#include "search_server.h"
#include "iterator_range.h"
#include "profile.h"
#include "parse.h"


#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <numeric>

void InvertedIndex::Add(string&& document) {
    docs.push_back(move((document)));

    const size_t docid = docs.size() - 1;
    for (string_view word : SplitIntoWords(docs.back())) {
        auto& docids = index[word];
        if (!docids.empty() && docids.back().first == docid) {
            ++docids.back().second;
        } else {
            docids.push_back({docid, 1});
        }
    }
}

const vector<pair<size_t, size_t>>& InvertedIndex::Lookup(string_view word) const {
    static const vector<pair<size_t, size_t>> empty;
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    } else {
        return empty;
    }
}

SearchServer::SearchServer(istream &document_input) {
    UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream &document_input) {
    InvertedIndex new_index;

    for (string current_document; getline(document_input, current_document);) {
        new_index.Add(move(current_document));
    }

    index = move(new_index);
}

void SearchServer::AddQueriesStream(
        istream &query_input, ostream &search_results_output
) {
    const auto doc_size = index.GetDocumentsSize();
    vector<size_t> docid_count(doc_size);
    vector<int64_t> docids(doc_size);
    for (string current_query; getline(query_input, current_query);) {
        docid_count.assign(docid_count.size(), 0);

        for (const auto& word : SplitIntoWords(current_query)) {
            for (const auto& [docid, count] : index.Lookup(word)) {
                docid_count[docid] += count;
            }
        }

        iota(docids.begin(), docids.end(), 0);

        partial_sort(
                begin(docids),
                Head(docids, 5).end(),
                end(docids),
                [&docid_count](int64_t lhs, int64_t rhs) {
                    return make_pair(docid_count[lhs], -lhs) > make_pair(docid_count[rhs], -rhs);
                }
        );

        search_results_output << current_query << ':';
        for (size_t docid : Head(docids, 5)) {
            const size_t hitcount = docid_count[docid];

            if (hitcount == 0) break;

            search_results_output << " {"
                                  << "docid: " << docid << ", "
                                  << "hitcount: " << hitcount << '}';
        }
        search_results_output << '\n';
    }
}
