/*
 * Copyright 2021 Hewlett Packard Enterprise Development LP
 * Other additional copyright holders may be indicated within.
 *
 * The entirety of this work is licensed under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except
 * in compliance with the License.
 *
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "chpl/resolution/resolution-queries.h"

#include "chpl/parsing/Parser.h"
#include "chpl/queries/ErrorMessage.h"
#include "chpl/queries/query-impl.h"
#include "chpl/uast/all-uast.h"

#include <cstdio>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

namespace chpl {

template<> struct update<resolution::ContainedScopesAndScopedSymbols> {
  bool operator()(resolution::ContainedScopesAndScopedSymbols& keep,
                  resolution::ContainedScopesAndScopedSymbols& addin) const {
    bool match = keep.idToScope == addin.idToScope &&
                 keep.scopeSymbolsToScopeIds == addin.scopeSymbolsToScopeIds;
    if (match) {
      return false; // no update required
    } else {
      keep.idToScope.swap(addin.idToScope);
      keep.scopeSymbolsToScopeIds.swap(addin.scopeSymbolsToScopeIds);
      return true; // updated
    }
  }
};

  /*
template<> struct update<resolution::ResolutionResult> {
  bool operator()(resolution::ResolutionResult& keep,
                  resolution::ResolutionResult& addin) const {
    bool match = keep.expr == addin.expr &&
                 keep.decl == addin.decl &&
                 keep.type == addin.type &&
                 keep.otherFns == addin.otherFns;
    if (match) {
      return false; // no update required
    } else {
      keep.expr = addin.expr;
      keep.decl = addin.decl;
      keep.type = addin.type;
      keep.otherFns.swap(addin.otherFns);
      return true; // updated
    }
  }
};

template<> struct update<resolution::ResolvedSymbol> {
  bool operator()(resolution::ResolvedSymbol& keep,
                  resolution::ResolvedSymbol& addin) const {
    bool match = keep.decl == addin.decl &&
                 keep.typeSubs == addin.typeSubs &&
                 keep.paramSubs == addin.paramSubs &&
                 keep.instantiationPoint == addin.instantiationPoint &&
                 keep.resolutionById.size() == addin.resolutionById.size();

    if (match) {
      // check also the resolutionById - we know sizes match here.
      size_t n = keep.resolutionById.size();
      for (size_t i = 0; i < n; i++) {
        resolution::ResolutionResult& keepR = keep.resolutionById[i];
        resolution::ResolutionResult& addinR = addin.resolutionById[i];
        if (keepR.expr == addinR.expr &&
            keepR.decl == addinR.decl &&
            keepR.type == addinR.type &&
            keepR.otherFns == addinR.otherFns) {
          // OK, it matches
        } else {
          match = false;
          break;
        }
      }
    }

    if (match) {
      return false; // no update required
    } else {
      keep.decl = addin.decl;
      keep.typeSubs.swap(addin.typeSubs);
      keep.paramSubs.swap(addin.paramSubs);
      keep.instantiationPoint = addin.instantiationPoint;
      keep.resolutionById.swap(addin.resolutionById);
      return true; // updated
    }
  }
};
*/

/*
template<> struct update<resolution::DefinedTopLevelNames> {
  bool operator()(resolution::DefinedTopLevelNames& keep,
                  resolution::DefinedTopLevelNames& addin) const {
template<> struct update<frontend::DefinedTopLevelNames> {
  bool operator()(frontend::DefinedTopLevelNames& keep,
                  frontend::DefinedTopLevelNames& addin) const {

    if (keep.module == addin.module) {
      return defaultUpdateVec(keep.topLevelNames, addin.topLevelNames);
    } else {
      keep.module = addin.module;
      keep.topLevelNames.swap(addin.topLevelNames);
      return false;
    }
  }
};
*/

/*
template<> struct update<resolution::Scope> {
  bool operator()(resolution::Scope& keep,
                  resolution::Scope& addin) const {

    bool match = keep.parent == addin.parent &&
                 keep.declared.size() == addin.declared.size() &&
                 keep.usesAndImports.size() == addin.usesAndImports.size();

    if (match) {
      // check also the contents of the map/vec
      match = keep.declared == addin.declared &&
              keep.usesAndImports == addin.usesAndImports;
    }

    if (match) {
      return false; // no update required
    } else {
      keep.parent.swap(addin.parent);
      keep.declared.swap(addin.declared);
      keep.usesAndImports.swap(addin.usesAndImports);
      return true; // updated
    }
  }
};
*/

namespace resolution {

using namespace uast;
using namespace types;

static
ID parentScopingSymbolId(Context* context, ID id) {
  return id.parentSymbolId(context);
}
/*
const uast::ASTNode* parentScopingSymbol(Context* context, ID id) {
  return parsing::idToAST(context, parentScopingSymbolId(context, id));
}*/

/*
static const ID&
parentForScopingSymbolQuery(Context* context, ID id);

static
void setParentForScopingSymbol(Context* context,
                               const ASTNode* ast,
                               const ASTNode* parent) {

  bool isInputQuery = false;
  context->querySetterUpdateResult<ID>(parentForScopingSymbolQuery,
                                       std::make_tuple(ast->id()),
                                       parent?parent->id():ID(),
                                       "parentForScopingSymbolQuery",
                                       isInputQuery);
}

static
void setParentForScopingSymbolRecursively(Context* context,
                                          const ASTNode* ast,
                                          const ASTNode* parent,
                                          const ID& findParentForId,
                                          ID& foundParent) {

  if (Builder::astTagIndicatesNewIdScope(ast->tag())) {
    if (ast->id() == findParentForId) {
      // update foundParent if we encountered that ID
      foundParent = parent->id();
    } else {
      // save it in the maps to keep it O(1)
      setParentForScopingSymbol(context, ast, parent);
    }
    // visit the children with parent as this node
    parent = ast;
  }

  for (const ASTNode* child : ast->children()) {
    setParentForScopingSymbolRecursively(context, child, parent,
                                         findParentForId, foundParent);
  }
}

static
void setParentsForScopingSymbolsInTopLevelModule(Context* context,
                                                 const Module* mod,
                                                 const ID& findParentForId,
                                                 ID& foundParent) {
  setParentForScopingSymbolRecursively(context, mod, nullptr,
                                       findParentForId, foundParent);
}

static const ID&
parentForScopingSymbolQuery(Context* context, ID id) {
  QUERY_BEGIN(parentForScopingSymbolQuery, context, id);

  // comments should be ruled out by parentForScopingSymbol().
  // the problem here is that they don't have an id.
  assert(!id.isEmpty());

  UniqueString path = context->filePathForID(id);
  auto moduleVec = parsing::parse(context, path);

  ID result;

  for (const Module* mod : moduleVec) {
    // To keep the process of computing parents O(1),
    // figure out the parents for all ASTs contained within this mod
    // and call setParentForScopingSymbol to save it.
    setParentsForScopingSymbolsInTopLevelModule(context, mod, id, result);
  }

  return QUERY_END(result);
}

ID parentExprForScopingSymbol(Context* context, ID id) {
  // if the ID is empty, return an empty ID
  if (id.isEmpty())
    return ID();

  // run the real query if the input is OK
  return parentForScopingSymbolQuery(context, id);
}
*/

struct GatherDeclsAndUses {
  DeclMap declared;
  UsesAndImportsVec usesAndImports;

  GatherDeclsAndUses() { }

  bool isEmpty() {
    return declared.empty() && usesAndImports.empty();
  }

  // Add NamedDecls to the map
  bool enter(const NamedDecl* d) {
    declared.insert({d->name(), d->id()});
    return false;
  }
  void exit(const NamedDecl* d) { }
  // Traverse into TupleDecl and MultiDecl looking for NamedDecls
  bool enter(const TupleDecl* d) {
    return true;
  }
  void exit(const TupleDecl* d) { }
  bool enter(const MultiDecl* d) {
    return true;
  }
  void exit(const MultiDecl* d) { }
  // make note of use/import
  bool enter(const Use* d) {
    usesAndImports.push_back(d->id());
    return false;
  }
  void exit(const Use* d) { }
  // ignore other AST nodes
  bool enter(const ASTNode* ast) {
    return false;
  }
  void exit(const ASTNode* ast) { }
};

static bool createsScope(asttags::ASTTag tag) {
  return Builder::astTagIndicatesNewIdScope(tag)
         || asttags::isSimpleBlockLike(tag)
         || asttags::isLoop(tag)
         || asttags::isCobegin(tag)
         || asttags::isConditional(tag)
         //|| asttags::isSelect(tag)
         //|| asttags::isTryCatch(tag)
         ;
}

static
void computeScopesForASTRecursively(Context* context,
                                   const uast::ASTNode* ast,
                                   ID parentScopeId,
                                   ContainedScopesAndScopedSymbols& result) {

  printf("in computeScopes id %s parentId %s\n",
          ast->id().toString().c_str(), parentScopeId.toString().c_str());

  if (createsScope(ast->tag())) {
    GatherDeclsAndUses visitor;
    // visit the child nodes (to e.g. look inside a Function
    // rather than collecting it as a NamedDecl).
    for (const ASTNode* child : ast->children()) {
      child->traverse(visitor);
    }

    // create the scope if we found any decls or if it's a Function etc
    if (visitor.isEmpty() == false ||
        Builder::astTagIndicatesNewIdScope(ast->tag())) {

      assert(!ast->id().isEmpty());

      Scope scope;
      scope.parentScopeId = parentScopeId;
      scope.id = ast->id();
      scope.declared.swap(visitor.declared);
      scope.usesAndImports.swap(visitor.usesAndImports);
      result.idToScope.emplace(ast->id(), std::move(scope));

      printf("Created new scope for id %s\n", ast->id().toString().c_str());

      // change parentScopeId to current scope.
      parentScopeId = ast->id();
    }
  }

  // Recurse into child AST nodes, but don't delve in to Scoped Symbols
  // e.g. a nested Function (these will be handled separately)
  for (const ASTNode* child : ast->children()) {
    if (Builder::astTagIndicatesNewIdScope(child->tag())) {
      result.scopeSymbolsToScopeIds.insert({child->id(), parentScopeId});
    } else {
      computeScopesForASTRecursively(context, child, parentScopeId, result);
    }
  }
}

// Computes Scopes for all contained expressions (e.g. Blocks).
// Stops at a Scoped Symbol (e.g. Function) but notes these.
static const ContainedScopesAndScopedSymbols&
scopesForScopingSymbolQuery(Context* context, ID id) {
  QUERY_BEGIN(scopesForScopingSymbolQuery, context, id);

  ContainedScopesAndScopedSymbols result;

  const uast::ASTNode* ast = parsing::idToAST(context, id);
  assert(ast != nullptr);
  if (ast != nullptr) {
    assert(Builder::astTagIndicatesNewIdScope(ast->tag()));

    ID inSymId = parentScopingSymbolId(context, id);
    ID parentId;

    if (!inSymId.isEmpty()) {
      const auto& parentScopes = scopesForScopingSymbolQuery(context, inSymId);
      // Now, we should see id there in the map to parent id
      auto search = parentScopes.scopeSymbolsToScopeIds.find(id);
      if (search != parentScopes.scopeSymbolsToScopeIds.end()) {
        parentId = search->second;
      } else {
        assert(false && "could not find parent scope");
      }
    }

    computeScopesForASTRecursively(context, ast, parentId, result);
  }

  return QUERY_END(result);
}

static const Scope* const& scopeForScopingSymbolQuery(Context* context, ID id) {
  QUERY_BEGIN(scopeForScopingSymbolQuery, context, id);

  const Scope* result = nullptr;

  const ContainedScopesAndScopedSymbols& scopes =
    scopesForScopingSymbolQuery(context, id);

  auto search = scopes.idToScope.find(id);
  if (search != scopes.idToScope.end()) {
    const Scope& ref = search->second;
    result = &ref;
  }

  return QUERY_END(result);
}

const Scope* scopeForScopingSymbol(Context* context, ID id) {
  return scopeForScopingSymbolQuery(context, id);
}

const Scope* scopeForModule(Context* context, ID id) {
  return scopeForScopingSymbol(context, id);
}

/*
static std::vector<UniqueString> getTopLevelNames(const Module* module) {
  std::vector<UniqueString> result;
  int nStmts = module->numStmts();
  for (int i = 0; i < nStmts; i++) {
    const Expression* expr = module->stmt(i);
    if (const NamedDecl* decl = expr->toNamedDecl()) {
      result.push_back(decl->name());
    }
  }
  return result;
}

const DefinedTopLevelNamesVec& moduleLevelDeclNames(Context* context,
                                                    UniqueString path) {
  QUERY_BEGIN(moduleLevelDeclNames, context, path);

  DefinedTopLevelNamesVec result;

  // Get the result of parsing modules
  const ModuleVec& p = parse(context, path);
  for (const Module* module : p) {
    result.push_back(DefinedTopLevelNames(module, getTopLevelNames(module)));
  }

  return QUERY_END(result);
}
*/

/*
using DeclsByName = std::unordered_map<UniqueString, const NamedDecl*>;

struct ResolvingScope {
  DeclsByName declsDefinedHere;
  const ResolvingScope* parentScope;
  // TODO: use'd / imported decls

  ResolvingScope(const ResolvingScope* parentScope)
    : declsDefinedHere(), parentScope(parentScope) {
  }

  const NamedDecl* innermostDeclWithName(UniqueString name) const {
    const ResolvingScope* cur = this;
    while (cur != nullptr) {
      auto search = cur->declsDefinedHere.find(name);
      if (search != cur->declsDefinedHere.end()) {
        // found an existing entry in the map, so use that
        return search->second;
      }
      cur = cur->parentScope;
    }
    return nullptr;
  }

  // TODO: something to return all of the decls with a particular name
  // (and their scopes?) (for fns)
};

class SingleResolver {
  Context* context;
  ResolvingScope* inScope;
  std::set<UniqueString>* undefinedInFn;

  ResolutionResult visit(const uast::Identifier* ident) {
    UniqueString name = ident->name();
    const NamedDecl* decl = inScope->findDeclForName(name);
    if (decl != nullptr) {
      // found an existing entry in the map, so we can add a resolution result.
      return ResolutionResult(ident, decl);
    } else {
      // nothing found in the map, so give an undefined symbol error,
      // unless we've already done so.
      if (undefinedInFn.count(name) == 0) {
        Location loc = parsing::locate(context, ident);
        auto error = ErrorMessage::build(loc,
                     "'%s' undeclared (first use this function)", name.c_str());
        context->queryNoteError(std::move(error));
        undefinedInFn.insert(name);
      }
    }
  }
  ResolutionResult visit(const uast::NamedDecl* decl) {
    UniqueString name = decl->name();
    auto search = inScope.declsDefinedHere.find(name);
    if (search != inScope.declsDefinedHere.end()) {
      const NamedDecl* prevDecl = search->second;
      // found an existing entry in the map, so give an error.
      Location prevLoc = parsing::locate(context, prevDecl);
      Location curLoc = parsing::locate(context, decl);
      auto error = ErrorMessage::build(prevLoc,
                   "'%s' has multiple definitions", name.c_str());
      error.addDetail(ErrorMessage::build(curLoc, "redefined here"));

      context->queryNoteError(std::move(error));
    } else {
      inScope.declsDefinedHere.insert(search, std::make_pair(name, decl));
    }
  }
};

// TODO: can we use an AST Visitor for the resolver?

// resolve some ast, recursively
static void resolveAST(Context* context,
                       const ASTNode* ast,
                       const ResolvingScope* parentScope,
                       ResolutionResultByPostorderID& resultByPostorderID,
                       std::set<UniqueString>& undefined) {

  if (const Identifier* ident = ast->toIdentifier()) {
    int postorderId = ident->id().postOrderId();
      assert(postorderId >= 0);
      // make sure the vector has room for this element
      if (postorderId >= (int)resultByPostorderID.size()) {
        resultByPostorderID.resize(postorderId+1);
      }
      resultByPostorderID[postorderId].expr = ident;
      resultByPostorderID[postorderId].decl = decl;

    return;
  }

  ResolvingScope newScope(parentScope);

  for (const ASTNode* child : ast->children()) {
    if (const NamedDecl* decl = child->toNamedDecl()) {
      UniqueString name = decl->name();
      auto search = newScope.declsDefinedHere.find(name);
      if (search != newScope.declsDefinedHere.end()) {
        const NamedDecl* prevDecl = search->second;
        // found an existing entry in the map, so give an error.
        Location prevLoc = parsing::locate(context, prevDecl);
        Location curLoc = parsing::locate(context, decl);
        auto error = ErrorMessage::build(prevLoc,
                     "'%s' has multiple definitions", name.c_str());
        error.addDetail(ErrorMessage::build(curLoc, "redefined here"));

        context->queryNoteError(std::move(error));
      } else {
        newScope.declsDefinedHere.insert(search, std::make_pair(name, decl));
      }
    }
  }

  // now we have recorded duplicate symbol errors, and
  // declsByName has unique'd names in it

  const ResolvingScope* useScope = nullptr;
  if (newScope.declsDefinedHere.size() == 0) {
    // No declarations, so no need to create a new scope.
    // This is an optimization to avoid unnecessary linked list traversal.
    useScope = parentScope;
  } else {
    // use the new scope we created
    useScope = &newScope;
  }

  // Delve further into the children of the node
  for (const ASTNode* child : ast->children()) {
    resolveAST(context, child, useScope, resultByPostorderID, undefined);
  }
}

const ResolvedSymbol&
resolveModule(Context* context, const Module* mod) {
  QUERY_BEGIN(resolveModule, context, mod);

  ResolutionResultByPostorderID resolutionById;
  std::set<UniqueString> undefined;
  resolveAST(context, mod, nullptr, resolutionById, undefined);

  ResolvedSymbol result;
  result.decl = mod;
  result.resolutionById.swap(resolutionById);

  return QUERY_END(result);
}

const ResolvedSymbolVec& resolveFile(Context* context, UniqueString path) {
  QUERY_BEGIN(resolveFile, context, path);

  ResolvedSymbolVec result;

  // parse the file and handle each module
  const parsing::ModuleVec& p = parsing::parse(context, path);
  for (const Module* mod : p) {
    const ResolvedSymbol& resolution = resolveModule(context, mod);
    result.push_back(&resolution);
  }

  return QUERY_END(result);
}
*/

} // end namespace resolution
} // end namespace chpl
