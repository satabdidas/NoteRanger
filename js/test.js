// David Prager Branner
// 20140728

;(function IIFE(window, document, undefined) {
    // Variables
    var currentURL,
    urlPrefix,
    whereWeAre,
    sought,
    tupleIndexes,
    indexNum,
    output,
    pathHash,
    pathTuple;

    // Main loop.
    document.addEventListener('DOMContentLoaded', function(){
        'use strict';

        // Different settings if running locally or on web.
        currentURL = window.location.href;
        if (currentURL.search(/http/) === 0) {
            // Don't use htmlpreview.github.io here; displays markdown, not HTML.
            // urlPrefix = "https://github.com/brannerchinese/notes/blob/gh-pages/notes/";
            urlPrefix = "https://github.com/satabdidas/RC_Notes/tree/master/";
            whereWeAre = "via HTTP.";
        }
        else {
            urlPrefix = "";
            whereWeAre = "from the filesystem.";
        }

        document.getElementById("whereRunning").innerHTML="This page was read " +
            whereWeAre + "<br/><br/>Enter your search term below:" +
            "<form>" +
            "<input type='text' id='searchTerm' />" +
            "<input type='button' onclick='getSought(\"" + urlPrefix +
            "\")' value='Enter search term'>" +
            "</form>";

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
})(window, document);

function getSought(urlPrefix) {
    if (urlPrefix === undefined) {
        urlPrefix = "";
        console.log("empty urlprefix\n");
    }
    sought = document.getElementById("searchTerm").value.toLowerCase();
    if (sought == null) {
        alert("Nothing found.");
        location.reload();
    }
    else {
        document.close();

        var terms = sought.split(" ");
        console.log("The query terms are " + terms);
        var pLists = getTermList(terms);
        pLists.sort(function(pList1, pList2) {
            return pList1.length - pList2.length;
        });
        var result = pLists[0];
        for (i = 1; i < pLists.length; ++i) {
            result = intersect(result, pLists[i]);
        }
        console.log(result);

        if (result.length == 0) {
            alert("Nothing found.");
            location.reload();
        }

        tupleIndexes = result;
        indexNum = 0;
        document.getElementById("whereRunning").innerHTML="Enter your next search term below:" +
            "<p id=\"whereRunning\"> </p>" +
            "<form><input type=\"text\" id=\"searchTerm\" />" +
            "<input type=\"button\" onclick=\"getSought('" +
            urlPrefix + "')\" " + "value=\"Submit search term\"></form>";
        document.getElementById("searchTerm").focus();
        output = "<p>Results for: "+sought+"</p><ul>";
        for (var i = 0; i < tupleIndexes.length; i++) {
            pathHash = tupleIndexes[indexNum++];
            pathTuple = TupleStorage[String(pathHash)];
            output += "<li><a href=\""  + urlPrefix + pathTuple[0] +
                "\" target=\"_blank\">" + pathTuple[1]+ "</a> (" +
                pathTuple[0] + ")</li>";
        }
        output += "</ul>";
        document.getElementById("results").innerHTML=output;
    }
}

function getTermList(terms) {
    var result = [];
    for (term in terms) {
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
        if (num1 == num2) {
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
