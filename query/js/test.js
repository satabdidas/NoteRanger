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
      urlPrefix = "https://github.com/satabdidas/RC_Notes/blob/master/";
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
  if (sought === null || typeof IndexEntries[sought] === "undefined") {
    console.log(sought, IndexEntries);
    alert("Nothing found.");
    location.reload();
  }
  else {
    document.close();
    tupleIndexes = IndexEntries[sought];
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
