#include "ESPAsync_Lang_Files.h"

#define PAGE_WM_HTTP_HEAD_START \
"<!DOCTYPE html>"\
"<html lang=\"en\">"\
"<head>"\
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>"\
"<title>{v}</title>"


#define PAGE_WM_HTTP_STYLE "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">"

/*
#define PALETTE_WM_BUT_BACKG "757575"
#define PALETTE_WM_BUT_FOCUS "a4a4a4"
#define PALETTE_WM_BUT_HOVER "494949"
#define PALETTE_WM_BUT_TEXT_COLOR "fff"
#define PALETTE_WM_MSG_BACKG "ef5350"
#define PALETTE_WM_MSG_BORDL "b61827"

#define PAGE_WM_HTTP_STYLE \
"<style>"\
  "div {"\
    "padding: 2px;"\
    "font-size: 1em;"\
  "}"\
  "body,"\
  "textarea,"\
  "input,"\
  "select {"\
    "background: 0;"\
    "border-radius: 0;"\
    "font: 16px sans-serif;"\
    "margin: 0;"\
  "}"\
  "textarea,"\
  "input,"\
  "select {"\
    "outline: 0;"\
    "font-size: 14px;"\
    "border: 1px solid #ccc;"\
    "padding: 8px;"\
    "width: 90%;"\
  "}"\
  ".btn a {"\
    "text-decoration: none;"\
  "}"\
  ".container {"\
    "margin: auto;"\
    "width: 90%;"\
  "}"\
  "@media (min-width: 1200px) {"\
    ".container {"\
      "margin: auto;"\
      "width: 30%;"\
    "}"\
  "}"\
  "@media (min-width: 768px) and (max-width: 1200px) {"\
    ".container {"\
      "margin: auto;"\
      "width: 50%;"\
    "}"\
  "}"\
  ".btn,"\
  "h2 {"\
    "font-size: 2em;"\
  "}"\
  "h1 {"\
    "font-size: 3em;"\
  "}"\
  ".btn {"\
    "background: #" PALETTE_WM_BUT_BACKG ";"\
    "border-radius: 4px;"\
    "border: 0;"\
    "color: #" PALETTE_WM_BUT_TEXT_COLOR ";"\
    "cursor: pointer;"\
    "display: inline-block;"\
    "margin: 2px 0;"\
    "padding: 10px 14px 11px;"\
    "width: 100%;"\
  "}"\
  ".btn:hover {"\
    "background: #" PALETTE_WM_BUT_HOVER ";"\
  "}"\
  ".btn:active,"\
  ".btn:focus {"\
    "background: #" PALETTE_WM_BUT_FOCUS ";"\
  "}"\
  "label > * {"\
    "display: inline;"\
  "}"\
  "form > * {"\
    "display: block;"\
    "margin-bottom: 10px;"\
  "}"\
  "textarea:focus,"\
  "input:focus,"\
  "select:focus {"\
    "border-color: #" PALETTE_WM_MSG_BORDL ";"\
  "}"\
  ".msg {"\
    "background: #" PALETTE_WM_MSG_BACKG ";"\
    "border-left: 5px solid #" PALETTE_WM_MSG_BORDL ";"\
    "padding: 1.5em;"\
  "}"\
  ".q {"\
    "float: right;"\
    "width: 64px;"\
    "text-align: right;"\
  "}"\
  ".l {"\
    "background: url(\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAMAAABEpIrGAAAALVBMVEX///8EBwfBwsLw8PAzNjaCg4NTVVUjJiZDRUUUFxdiZGSho6OSk5Pg4eFydHTCjaf3AAAAZElEQVQ4je2NSw7AIAhEBamKn97/uMXEGBvozkWb9C2Zx4xzWykBhFAeYp9gkLyZE0zIMno9n4g19hmdY39scwqVkOXaxph0ZCXQcqxSpgQpONa59wkRDOL93eAXvimwlbPbwwVAegLS1HGfZAAAAABJRU5ErkJggg==\")"\
      "no-repeat left center;"\
    "background-size: 1em;"\
  "}"\
  "input[type=\"checkbox\"] {"\
    "float: left;"\
    "width: 20px;"\
  "}"\
  ".table td {"\
    "padding: 0.5em;"\
    "text-align: left;"\
  "}"\
  ".table tbody > :nth-child(2n-1) {"\
    "background: #ddd;"\
  "}"\
  "fieldset {"\
    "border-radius: 0.5rem;"\
    "margin: 0px;"\
  "}"\
"</style>" */



#define PAGE_WM_HTTP_SCRIPT_NTP_MSG \
"<p>" LANG_WM_HTTP_SCRIPT_NTP_MSG_1 "<b><label id='timezone'></b><script>document.getElementById('timezone').innerHTML = timezone.name();</script></p>"


#define PAGE_WM_HTTP_HEAD_END \
"</head>"\
"<body>"\
  "<div class=\"container\">"\
  "<p style=\"text-align: center;\"><img style=\"width:90%;height:auto;\", src=\"logo.svg\"></p>"\
  "<div style=\"text-align:left;display:inline-block;min-width:260px;\">"


#define PAGE_WM_HTTP_PORTAL_OPTIONS \
"<form action=\"/wifi\" method=\"get\"><button class=\"btn\">" LANG_WM_HTTP_PORTAL_OPTIONS_1 "</button></form><br/>"\
"<form action=\"/i\" method=\"get\"><button class=\"btn\">" LANG_WM_HTTP_PORTAL_OPTIONS_2 "</button></form><br/>"\
"<form action=\"/close\" method=\"get\"><button class=\"btn\">" LANG_WM_HTTP_PORTAL_OPTIONS_3 "</button></form><br/>"


#define PAGE_WM_HTTP_FORM_START \
"<form method=\"get\" action=\"wifisave\">"\
"<fieldset>"\
  "<div>"\
    "<label>" LANG_WM_HTTP_FORM_START_SSID "</label><input id=\"s\" name=\"s\" length=32 placeholder=\"SSID\">"\
    "<div></div>"\
  "</div>"\
  "<div>"\
    "<label>" LANG_WM_HTTP_FORM_START_PASS "</label><input id=\"p\" name=\"p\" length=64 placeholder=\"password\">"\
    "<div></div>"\
  "</div>"\
  "<div>"\
    "<label>" LANG_WM_HTTP_FORM_START_SSID "1</label><input id=\"s1\" name=\"s1\" length=32 placeholder=\"SSID1\">"\
    "<div></div>"\
  "</div>"\
  "<div>"\
    "<label>" LANG_WM_HTTP_FORM_START_PASS "</label><input id=\"p1\" name=\"p1\" length=64 placeholder=\"password1\">"\
    "<div></div>"\
  "</div>"\
"</fieldset>"


#define PAGE_WM_HTTP_FORM_END \
"<button class=\"btn\" type=\"submit\">" LANG_WM_HTTP_FORM_END_SAVE "</button></form>"


#define PAGE_WM_HTTP_SAVED \
"<div class=\"msg\">" LANG_WM_HTTP_SAVED_1 LANG_WM_HTTP_SAVED_2 "</div>"


#define PAGE_WM_HTTP_AVAILABLE_PAGES \
"<h3>" LANG_WM_HTTP_AVAILABLE_PAGES_TITLE "</h3>"\
"<table class=\"table\">"\
  "<thead>"\
    "<tr>"\
      "<th>" LANG_WM_HTTP_AVAILABLE_PAGES_1 "</th>"\
      "<th>" LANG_WM_HTTP_AVAILABLE_PAGES_2 "</th>"\
    "</tr>"\
  "</thead>"\
  "<tbody>"\
    "<tr>"\
      "<td><a href=\"/\">/</a></td>"\
      "<td>" LANG_WM_HTTP_AVAILABLE_PAGES_MENU "</td>"\
    "</tr>"\
    "<tr>"\
      "<td><a href=\"/wifi\">/wifi</a></td>"\
      "<td>" LANG_WM_HTTP_AVAILABLE_PAGES_WIFI "</td>"\
    "</tr>"\
    "<tr>"\
      "<td><a href=\"/wifisave\">/wifisave</a></td>"\
      "<td>" LANG_WM_HTTP_AVAILABLE_PAGES_SAVE "</td>"\
    "</tr>"\
    "<tr>"\
      "<td><a href=\"/close\">/close</a></td>"\
      "<td>" LANG_WM_HTTP_AVAILABLE_PAGES_CLOSE "</td>"\
    "</tr>"\
    "<tr>"\
      "<td><a href=\"/i\">/i</a></td>"\
      "<td>" LANG_WM_HTTP_AVAILABLE_PAGES_INFO "</td>"\
    "</tr>"\
    "<tr>"\
      "<td><a href=\"/r\">/r</a></td>"\
      "<td>" LANG_WM_HTTP_AVAILABLE_PAGES_RESET "</td>"\
    "</tr>"\
    "<tr>"\
      "<td><a href=\"/state\">/state</a></td>"\
      "<td>" LANG_WM_HTTP_AVAILABLE_PAGES_STATE "</td>"\
    "</tr>"\
"</table>"
