#include "ESPAsync_Lang_Files.h"

#define PAGE_WM_HTTP_HEAD_START \
"<!DOCTYPE html>"\
"<html lang=\"en\">"\
"<head>"\
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>"\
"<title>{v}</title>"


#define PAGE_WM_HTTP_STYLE \
"<style>div{padding:2px;font-size:1em;}body,textarea,input,select{background: 0;border-radius: 0;font: 16px sans-serif;margin: 0}textarea,input,select{outline: 0;font-size: 14px;border: 1px solid #ccc;padding: 8px;width: 90%}.btn a{text-decoration: none}.container{margin: auto;width: 90%}@media(min-width:1200px){.container{margin: auto;width: 30%}}@media(min-width:768px) and (max-width:1200px){.container{margin: auto;width: 50%}}.btn,h2{font-size: 2em}h1{font-size: 3em}.btn{background: #0ae;border-radius: 4px;border: 0;color: #fff;cursor: pointer;display: inline-block;margin: 2px 0;padding: 10px 14px 11px;width: 100%}.btn:hover{background: #09d}.btn:active,.btn:focus{background: #08b}label>*{display: inline}form>*{display: block;margin-bottom: 10px}textarea:focus,input:focus,select:focus{border-color: #5ab}.msg{background: #def;border-left: 5px solid #59d;padding: 1.5em}.q{float: right;width: 64px;text-align: right}.l{background: url('data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAMAAABEpIrGAAAALVBMVEX///8EBwfBwsLw8PAzNjaCg4NTVVUjJiZDRUUUFxdiZGSho6OSk5Pg4eFydHTCjaf3AAAAZElEQVQ4je2NSw7AIAhEBamKn97/uMXEGBvozkWb9C2Zx4xzWykBhFAeYp9gkLyZE0zIMno9n4g19hmdY39scwqVkOXaxph0ZCXQcqxSpgQpONa59wkRDOL93eAXvimwlbPbwwVAegLS1HGfZAAAAABJRU5ErkJggg==') no-repeat left center;background-size: 1em}input[type='checkbox']{float: left;width: 20px}.table td{padding:.5em;text-align:left}.table tbody>:nth-child(2n-1){background:#ddd}fieldset{border-radius:0.5rem;margin:0px;}</style>"

#define PAGE_WM_HTTP_SCRIPT_NTP_MSG \
"<p>" LANG_WM_HTTP_SCRIPT_NTP_MSG_1 "<b><label id='timezone'></b><script>document.getElementById('timezone').innerHTML = timezone.name();</script></p>"


#define PAGE_WM_HTTP_HEAD_END \
"</head>"\
  "<body>"\
    "<div class=\"container\">"\
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