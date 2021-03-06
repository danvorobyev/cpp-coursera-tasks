#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <unordered_map>
#include <string>
#include <deque>

using namespace std;

#define MAX_DOCUMENTS 50000

class InvertedIndex {
public:
    void Add(string&& document);

    const vector<pair<size_t, size_t>>& Lookup(string_view word) const;

    const string &GetDocument(size_t id) const {
        return docs[id];
    }

    const size_t GetDocumentsSize() const {
        return docs.size();
    }


private:
    unordered_map<string_view, vector<pair<size_t, size_t>>> index;
    deque<string> docs;
};

class SearchServer {
public:
    SearchServer() = default;

    explicit SearchServer(istream &document_input);

    void UpdateDocumentBase(istream &document_input);

    void AddQueriesStream(istream &query_input, ostream &search_results_output);

private:
    InvertedIndex index;
};
