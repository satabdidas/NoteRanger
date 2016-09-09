// David Prager Branner
// 20140728

;(function IIFE(window, document, undefined) {
    'use strict';

    // Variables
    var currentURL, urlPrefix, whereWeAre;

    // Main loop.
    document.addEventListener('DOMContentLoaded', function(){

        // Different settings if running locally or on web.
        currentURL = window.location.href;
        if (currentURL.search(/http/) === 0) {
            // Don't use htmlpreview.github.io here; displays markdown, not HTML.
            urlPrefix = "https://github.com/satabdidas/RC_Notes/tree/master/";
            whereWeAre = "via HTTP.";
        }
        else {
            urlPrefix = "";
            whereWeAre = "from the filesystem.";
        }

        document.getElementById("searchForm").addEventListener('submit', getSought);
        // Set focus.
        document.getElementById("searchTerm").focus();

        // Errors.
        if (IndexEntries === null) {
            alert("IndexEntries is null");
        }
        else if (TupleStorage === null) {
            alert("TupleStorage is null");
        }
    });

    function getSought(event) {
        event.preventDefault();
        var sought = document.getElementById("searchTerm").value.toLowerCase();
        if (sought == null) {
            alert("Nothing found.");
            location.reload();
        }
        else {
            document.close();

            var result = getResult(sought);
            if (result.length === 0) {
                alert("Nothing found.");
                location.reload();
            }
            displayResult(result, sought);
        }
    }

    function getTermList(terms) {
        var result = [];
        for (var term in terms) {
            if (term != null && IndexEntries[terms[term]] != null) {
                result.push(IndexEntries[terms[term]]);
                console.log("The posting list for " + terms[term] + " is " + IndexEntries[terms[term]]);
            }
        }
        return result;
    }

    function intersect(pList1, pList2) {
        var i = 0, j = 0;
        var result = [];

        while (i < pList1.length && j < pList2.length) {
            var num1 = parseInt(pList1[i]);
            var num2 = parseInt(pList2[j]);
            if (num1 === num2) {
                result.push(pList1[i]);
                i++;
                j++;
            } else if (num1 < num2) {
                ++i;
            } else {
                ++j;
            }
        }

        return result;
    }

    function getResult(sought) {
        var terms = sought.split(" ");
        console.log("The query terms are " + terms);
        var pLists = getTermList(terms);
        pLists.sort(function(pList1, pList2) {
            return pList1.length - pList2.length;
        });
        var result = pLists[0];
        for (var i = 1; i < pLists.length; ++i) {
            result = intersect(result, pLists[i]);
        }
        console.log(result);
        return result;
    }

    function displayResult(result, sought) {
        var tupleIndexes = result;
        var indexNum = 0;

        var searchTerm = document.getElementById("searchTerm");
        searchTerm.value = "";
        searchTerm.focus();
        var output = "<p>Results for: "+sought+"</p><ul>";
        for (var i = 0; i < tupleIndexes.length; i++) {
            var pathHash = tupleIndexes[indexNum++];
            var pathTuple = TupleStorage[String(pathHash)];
            output += "<li><a href=\""  + urlPrefix + pathTuple[0] +
                "\" target=\"_blank\">" + pathTuple[1]+ "</a> (" +
                pathTuple[0] + ")</li>";
        }
        output += "</ul>";
        document.getElementById("results").innerHTML=output;
    }

})(window, document);
