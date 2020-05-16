/*
 * WTFPL with no warrenty
*/

#include <iostream>
#include <cmath>

using namespace std;

/*
 * This table convert all punctuations in full-width into correct vertical way
 * that listed on https://language.moe.gov.tw/001/Upload/files/site_content/M0001/hau/f2.html
 * The website above is provided by Ministry of Education Republic of China (Taiwan)
 * and released with CC BY-NC-ND 2.5 TW
*/

string fullWidthCorrrection(string input) {
  string correction;
  correction = input;
  // Ellipsis
  if (input == "…" || input == "⋯" || input == "⋮" || input == "...") { // U+2026 and U+22EF and U+22EE and triple dot
    correction = "︙"; // U+FE19
  }
  // Quotation Marks
  if (input == "〝" || input == "「") { // U+301D and U+300C
    correction = "﹁"; // U+FE41
  }
  if (input == "『") { // U+300E
    correction = "﹃"; // U+FE43
  }
  if (input == "〞" || input == "」" || input == "〟") { // U+301E and U+300D and U+301F
    correction = "﹂"; // U+FE42
  }
  if (input == "』") { // U+300F
    correction = "﹄"; // U+FE44
  }
  // Parenthesis
  if (input == "﹙" || input == "（" || input == "⏜") { // U+FE59 and U+FF08 and U+23DC
    correction = "︵"; // U+FE35
  }
  if (input == "﹚" || input == "）" || input == "⏝") { // U+FE5A and U+FF09 and U+23DD
    correction = "︶"; // U+FE36
  }
  // Dash
  if (input == "─" || input == "━" || input == "—") { // U+2500 and U+2501 and U+2014
    correction = "︱"; // U+FE31
  }
  //Angle Brackets
  if (input == "〈" || input == "〈") { // U+2329 and U+3008
    correction = "︿"; // U+FE3F
  }
  if (input == "《") { // U+300A
    correction = "︽"; // U+FE3D
  }
  if (input == "〉" || input == "〉") { // U+232A and U+3009
    correction = "﹀"; // U+FE40
  }
  if (input == "》") { // U+300B
    correction = "︾"; // U+FE3E
  }
  // Low Line
  if (input == "＿") { // U+FF3F
    correction = "︳"; // U+FE33
  }
  // Wavy Low Line
  if (input == "﹏") { // U+FE4F
    correction = "︴"; // U+FE34
  }
  // Tilde
  /* Tilde actually not work since Unicode doesnt have a vertical Tilde
   * or Wave Dash. Therefore, users have to create the symbol by themselves
   * just like the interrobang
  */
  if (input == "〜") { // U+301C
    correction = "～"; // U+FF5E
  }
  return correction;
}

void firstRowCheck(bool tfFirstRow) {
  if (tfFirstRow) {
    cout << "Enter the first line: " << endl;
  }
  else {
    cout << "Enter the next line: " << endl;
  }
}

void lastRowCheck(bool tfLastRow, int numLastRowCheck) {
  if (tfLastRow) {
    cout << "Total " << numLastRowCheck+1 << " for now. Analyzing..." << endl;
  }
  else {
    cout << "Total " << numLastRowCheck+1 << " for now. ";
  }
}

int main() {
  bool firstTime = true;
  bool lastRow = false;

/*
 * check number of rows
*/

  int rowNum;
  cout << "Plz enter the number of rows: ";
  cin >> rowNum;
  cout << rowNum << " rows will be convert to vertical text. ";
  string text[rowNum];
  for (int i = 0; i < rowNum; i++) {
    firstRowCheck(firstTime);
    // cout << i << endl;
    getline(cin >> std::ws, text[i]); // I have no idea what does "::ws" do but will get error if without it.
    cout << "You entered " << text[i] << endl;
    firstTime = false;
    if (i+1 >= rowNum) {
      lastRow = true;
    }
    lastRowCheck(lastRow, i);
  }

/*
 * check length per rows
*/

  int length, lengthReal; // for now only CJK allowed.
  int large = 0;
  for (int i = 0; i < rowNum; i++) {
    large = fmax(text[i].length(), large);
    // cout << large << endl;
    // cout << text[i].length() << " < length" << endl;
    // cout << text[i].size() << " < size" <<endl;
  }
  length = large; // for now length == large
  lengthReal = length / 3;
  cout << "CJK characters (in unicode) per row: " << lengthReal << endl;

/*
 * check encoding and others. For now this part not work.
*/

  // Nothing here.

/*
 * add full-width unicode space to make each row same length
*/
  // int tempForLen;
  for (int i = 0; i < rowNum; i++) {
    while (text[i].length() < large) {
      // tempForLen = text[i].length() * 3 - 1;
      // text[i] += "？";
      text[i] += " "; // Unicode Character “ ” (U+2003) Name:	Em Space
    }
  }

/*
 * Test output 1.
*/

  // for (int i = 0; i < rowNum; i++) {
  //   cout << text[i] << "測試" << endl;
  // }
  // cout << text[1][0] << text[1][1] << text[1][2] << endl;

/*
 * converting process
*/

  // string textRow[rowNum][lengthReal];
  // for (int i = 0; i < rowNum; i++) {
  //   for (int j = 0; j < lengthReal; j++) {
  //     textRow[i][j] = text[i][j];
  //     textRow[i][j] += text[i][j + 1];
  //     textRow[i][j] += text[i][j + 2];
  //   }
  // }
  cout << "converting..." << endl;
  // string rowResult = "";
  string outputText[lengthReal][rowNum];
  string charResult = "";
  // string testResult = "";
  int leftNum, m, n, o;
  for (int j = 0; j < lengthReal; j++) {
    // rowResult = "";
    for (int i = 0; i < rowNum; i++) {
      leftNum = rowNum - i - 1;
      m = 3 * j;
      n = 3 * j + 1;
      o = 3 * j + 2;
      // rowResult += text[leftNum][m];
      // rowResult += text[leftNum][n];
      // rowResult += text[leftNum][o];
      charResult += text[leftNum][m];
      charResult += text[leftNum][n];
      charResult += text[leftNum][o];
      charResult = fullWidthCorrrection(charResult);
      outputText[i][j] = charResult;
      cout << outputText[i][j];
      charResult = "";
      // testResult += rowResult;
    }
    cout << endl;
    // cout << rowResult << endl;
    // cout << testResult << endl;
  }
  // cout << "done" << endl;

/*
 * Test output 2.
*/

  // for (int i = 0; i < rowNum; i++) {
  //   for (int j = 0; j < lengthReal; j++) {
  //     cout << textRow[i][j] << "測試" << endl;
  //   }
  // }
  cout << "special charactors u may need: " << endl;
  cout << "┃& &│&︱&⋮&〜&．&⋯" << endl; // U+2503 and U+2003 and U+2502 and U+FE31 and U+22EE and U+FF5E and U+FF0E and U+22EF
  return 0;
}
