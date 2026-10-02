#pragma once
#include <string>
#include <vector>

// Starter list: the daily word is picked from ANSWERS.
// Replace with a full ~2,300-word answer list for real play.
static const std::vector<std::string> ANSWERS = {
    "about","other","which","their","there","first","would","these","click","price",
    "state","email","world","music","after","video","where","books","links","years",
    "order","items","group","under","games","could","great","hotel","store","terms",
    "right","local","those","using","phone","forum","based","black","check","index",
    "being","women","today","south","pages","found","house","photo","power","while",
    "three","total","place","think","north","posts","media","water","since","guide",
    "board","white","small","times","sites","level","hours","image","title","shall",
    "class","still","money","every","visit","tools","reply","value","press","learn",
    "print","stock","point","sales","large","table","start","model","human","movie",
    "going","study","staff","again","never","users","topic","below","party","login",
    "legal","above","quote","story","rates","young","field","paper","girls","night"
};

// Extra words accepted as guesses but never chosen as the answer.
// Replace with a full ~10,000-word valid-guess list.
static const std::vector<std::string> EXTRA = {
    "crane","slate","adieu","stare","raise","irate","trace","crate"
};
