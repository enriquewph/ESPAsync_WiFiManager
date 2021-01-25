#include "ESPAsync_Lang_Files.h"

#define PAGE_WM_HTTP_HEAD_START \
"<!DOCTYPE html>"\
"<html lang=\"en\">"\
"<head>"\
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>"\
"<title>{v}</title>"


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
    "background: #e30016;"\
    "border-radius: 4px;"\
    "border: 0;"\
    "color: #fff;"\
    "cursor: pointer;"\
    "display: inline-block;"\
    "margin: 2px 0;"\
    "padding: 10px 14px 11px;"\
    "width: 100%;"\
  "}"\
  ".btn:hover {"\
    "background: #b50011;"\
  "}"\
  ".btn:active,"\
  ".btn:focus {"\
    "background: #cc0013;"\
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
    "border-color: #62b121;"\
  "}"\
  ".msg {"\
    "background: #c0dfa6;"\
    "border-left: 5px solid #62b121;"\
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
"</style>"



#define PAGE_WM_HTTP_SCRIPT_NTP_MSG \
"<p>" LANG_WM_HTTP_SCRIPT_NTP_MSG_1 "<b><label id='timezone'></b><script>document.getElementById('timezone').innerHTML = timezone.name();</script></p>"


#define PAGE_WM_HTTP_HEAD_END \
"</head>"\
"<body>"\
  "<div class=\"container\">"\
  "<p style=\"text-align: center;\"><svg width=\"350\" height=\"43.31\" viewBox=\"0 0 105.73 13.085\" xmlns=\"http://www.w3.org/2000/svg\"><g transform=\"matrix(.26458 0 0 .26458 -38.108 -65.682)\" fill-rule=\"evenodd\"><g fill=\"#e30016\"><path d=\"m331.44 248.25c-1.6971 0-3.6925 1.4971-6.1879 4.6921l-24.153 31.238-4.4919-31.238c-0.3994-3.195-1.4967-4.6921-3.094-4.6921-1.1967 0-2.2953 0.4006-3.4937 1.3968-1.0969 0.8989-1.9949 1.9966-2.6942 3.2953l-20.561 38.824-2.6942 5.0893h8.3833l16.668-33.533 4.6916 30.839c0.2995 2.1975 1.4963 3.1934 3.3922 3.1934 1.6967 0 3.3939-0.9959 4.9912-3.0935l24.054-30.939-4.2919 33.533h8.3837l4.1925-43.914c0.0982-1.2987-0.101-2.3964-0.5998-3.2953-0.5981-0.8976-1.4966-1.3968-2.4941-1.3968z\"/><path d=\"m540.52 248.25c-1.6971 0-3.6925 1.4971-6.1878 4.6921l-24.152 31.238-4.4941-31.238c-0.3977-3.195-1.495-4.6921-3.0923-4.6921-1.1967 0-2.2965 0.4006-3.4933 1.3968-1.0973 0.8989-1.9953 1.9966-2.6946 3.2953l-20.562 38.824-2.6946 5.0893h8.385l16.668-33.533 4.69 30.839c0.3015 2.1975 1.4978 3.1934 3.3938 3.1934 1.6971 0 3.3939-0.9959 4.9912-3.0935l24.052-30.939-4.292 33.533h8.385l4.1925-43.914c0.0966-1.2987-0.1023-2.3964-0.5998-3.2953-0.5998-0.8976-1.4979-1.3968-2.4954-1.3968z\"/><path d=\"m358.97 248.94h-7.3859l-14.872 47.808h7.3858l12.476-40.222z\"/><path d=\"m269.42 272.3c2.1955-6.987 1.8956-12.675-0.6996-16.968-0.1988-0.1993-0.3977-0.5-0.4988-0.6988-2.7952-3.7916-7.0859-5.6896-13.074-5.6896h-13.474c-5.6891 0.3003-11.078 2.4962-15.969 6.3884-5.3901 4.2923-9.1824 9.9806-11.378 16.968-0.9983 3.1933-1.4971 6.1874-1.4971 8.8817 0 3.1946 0.6984 6.0888 2.0961 8.684 2.5944 4.5898 7.0859 6.8863 13.274 6.8863h13.475c5.69-0.3977 11.079-2.6946 16.17-6.8863 4.5902-3.8917 8.0835-8.5842 10.379-14.172 0.3994-1.099 0.7991-2.1954 1.1984-3.3934zm-7.6861 0.6984c-1.3969 4.5902-3.891 8.2831-7.3842 11.177-3.5944 2.7956-7.3876 4.2927-11.579 4.2927h-11.978c-4.0914 0-6.9865-1.4971-8.7831-4.2927-1.6967-2.8943-1.8963-6.5872-0.4987-11.177 1.4975-4.5906 3.992-8.3838 7.5851-11.378 3.5939-2.8943 7.3858-4.3913 11.479-4.3913h11.978c4.0902 0 7.086 1.497 8.7831 4.3913 1.7961 2.9945 1.8955 6.7877 0.3977 11.378z\"/><path d=\"m475.66 271.7c1.6971-5.8888 1.6971-10.678 0-14.572-0.3011-0.5981-0.5994-1.1967-0.8981-1.7961-2.6946-4.2915-7.1853-6.3884-13.572-6.3884h-13.476c-5.6875 0.3003-11.08 2.4962-15.968 6.3884-5.3921 4.2923-9.1836 9.9806-11.381 16.968-2.1947 7.0863-1.9954 12.875 0.5994 17.566 2.5952 4.5898 7.0892 6.8863 13.274 6.8863h13.476c5.6875-0.3977 11.08-2.6946 16.167-6.8863 5.4886-4.6908 9.3828-10.479 11.577-17.566 0.1023-0.1993 0.1023-0.3993 0.2017-0.5998zm-7.7852 1.2982c-1.495 4.5902-3.9936 8.2831-7.484 11.177-3.5927 2.7956-7.3871 4.2927-11.58 4.2927h-11.975c-4.096 0-6.9894-1.4971-8.7827-4.2927-1.7-2.8943-1.8988-6.5872-0.5033-11.177 1.4979-4.5906 3.9937-8.3838 7.5864-11.378 3.5927-2.8943 7.3875-4.3913 11.477-4.3913h11.978c4.093 0 7.0888 1.497 8.7826 4.3913 1.7995 2.9945 1.8989 6.7877 0.5004 11.378z\"/><path d=\"m427.5 248.94h-10.98l-24.599 18.119-0.7405-0.9522-12.978-17.166h-10.977l18.166 23.455-27.648 20.36-5.4887 3.9936h10.98l24.599-18.119 0.7405 0.9525 12.978 17.166h10.977l-18.166-23.454 27.648-20.36z\"/></g><path d=\"m164.58 248.6h17.763l-17.146 49.104h-15.294c-5.0755 0-7.2698-5.4861-4.9383-12.275l9.739-27.844c1.7144-4.9386 6.1725-8.9847 9.8759-8.9847z\" fill=\"#1b1918\"/><path d=\"m185.02 248.6h15.294c5.0066 0 7.2014 5.4861 4.8696 12.276l-9.7387 27.844c-1.7146 4.9374-6.1721 8.9841-9.8759 8.9841h-17.695z\" fill=\"#62b121\"/><g fill=\"#e30016\"><path d=\"m180.87 292.97 7.0875-4.9286-3.5209-5.0156h-6.8273l-3.4721 9.9442z\"/><path d=\"m186.26 277.49 7.0875-4.9295-3.5209-5.0153h-6.8272l-3.4722 9.9448z\"/><path d=\"m191.21 263.32 7.0875-4.9292-3.5209-5.0159h-6.8267l-3.4727 9.9451z\"/></g><g fill=\"#fff\"><path d=\"m168.94 277.47 10.081-28.871h-2.4377l-10.081 28.871z\"/><path d=\"m165.93 269.67 7.3579-21.073h-2.4381l-7.3579 21.073z\"/><path d=\"m162.36 263.48 5.1957-14.88h-2.4378l-5.1959 14.88z\"/></g></g></svg></p>"\
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
