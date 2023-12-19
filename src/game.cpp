#include "game.h"

game::game() {
    MISSIONS = MAIL = LOOT = ADVENTURE = FRIENDS = SHOP = ARENA = GUARDIAN = MOCK = TRIAL = AGENCY = ALLIANCE = SECRETFLOOR = TRYADVENTURE = false;
    background = Template(backg, Gray);
    dimX = 1080;
    dimY = 1920;
    package = "com.netmarble.tog";
    activity = "com.netmarble.tog/.TogActivity";
    fillPopup();
    sys.createpaths(templates);
    mac = macroConfig(package, activity);
    firstboot = true;
    restartMacro = true;
    endmacro = false;
}

void game::initActivities()
{

    std::vector<std::tuple<bool*, std::string>> alltuples{
        std::tuple<bool*, std::string>(&MISSIONS, "MISSIONS"),
        std::tuple<bool*, std::string>(&MAIL, "MAIL"),
        std::tuple<bool*, std::string>(&LOOT, "LOOT"),
        std::tuple<bool*, std::string>(&ADVENTURE, "ADVENTURE"),
        std::tuple<bool*, std::string>(&FRIENDS, "FRIENDS"),
        std::tuple<bool*, std::string>(&SHOP, "SHOP"),
        std::tuple<bool*, std::string>(&ARENA, "ARENA"),
        std::tuple<bool*, std::string>(&MOCK, "MOCK"),
        std::tuple<bool*, std::string>(&TRIAL, "TRIAL"),
        std::tuple<bool*, std::string>(&AGENCY, "AGENCY"),
        std::tuple<bool*, std::string>(&ALLIANCE, "ALLIANCE"),
        std::tuple<bool*, std::string>(&TRYADVENTURE, "TRYADVENTURE"),
        std::tuple<bool*, std::string>(&GUARDIAN, "GUARDIAN"),
        std::tuple<bool*, std::string>(&SECRETFLOOR, "SECRETFLOOR"),
    };
    char letter = 'a';
    for (int i = 0; i < alltuples.size(); ++i) {
        allActivities.insert({ letter,alltuples.at(i) });
        ++letter;
        if (letter > 'z')letter = 'A';
    }
}


void game::selectActivity() {
    int duration = 30;
    int timeleft;
    std::string choix;
    bool choseFavPreset = false;
    bool chosePreset = false;
    std::string textseconds = "Seconds left: ";
    std::cout << std::endl << "Type which activity you wanna do:" << std::endl;
    std::cout << "ALL : 0" << std::endl;
    std::cout << "Unknown rewards: 1" << std::endl;
    char let = 'a';
    while (let != 'Z') {
        bool pres;
        std::tuple<bool*, std::string>activity = getActivity(let, pres);
        if (pres) {
            std::cout << std::get<1>(activity) << ":" << let << "  ";
        }
        if (let == 'z') {
            let = 'A';
            continue;
        }
        ++let;
    } 
    std::cout << "for example: abjdlm or ABJghDd or 0" << std::endl << std::endl;
    std::cout << "Type P to choose preset" << std::endl;
    std::cout << "Type F to choose favorite Preset" << std::endl;
    std::cout << "Type S to Skip" << std::endl;
    std::cout << "Validate your input with Enter" << std::endl;
    std::cout << std::endl << "Seconds left: ";
    auto start = std::chrono::steady_clock::now();
    long long int elapsed = 0;
    long long int lastelapsed = elapsed;
    int maxchar = 0;
    int nbchar = 0;
    int lastnbchar = 0;
    int i = duration;
    while (i > 0) {
        i /= 10;
        maxchar++;
    }
    std::cout << duration;
    mac.readMcfilefavouritePreset();

    do {
        auto now = std::chrono::steady_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
        timeleft = duration - elapsed;
        if (lastelapsed != elapsed) {
            nbchar = 0;
            i = timeleft;
            while (i != 0) {
                i /= 10;
                nbchar++;
            }
            for (int j = 0; j < maxchar + textseconds.length(); ++j) {
                std::cout << "\b";
            }
            std::cout << textseconds;
            for (int j = 0; j < 2 * maxchar - nbchar; ++j) {
                std::cout << " ";
            }
            for (int j = 0; j < maxchar; ++j) {
                std::cout << "\b";
            }
            std::cout << timeleft;
            lastelapsed = elapsed;
        }
        if (ml.isKeyPressed(sf::Keyboard::P)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            std::cout << std::endl << "Type Preset: ";
            std::cin.clear();
            std::cin >> choix;
            chosePreset = true;
        }

        if (ml.isKeyPressed(sf::Keyboard::F)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            std::cout << "Type favorite Preset: ";
            std::cin.clear();
            std::cin >> choix;
            mac.favouritePreset = choix;
            mac.updateFavouritePreset(mac.favouritePreset);
        }

        if (ml.isKeyPressed(sf::Keyboard::S) && elapsed > 0.5f) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            break;
        }

    } while (timeleft > 0 && !chosePreset);

    if (!chosePreset) {
        choix = mac.favouritePreset;
    }
    std::cout << std::endl;

    for (int i = 0; i < choix.size(); i++) {
        bool pres;
        char ca = choix[i];
        std::tuple<bool*, std::string>activity = getActivity(ca, pres);
        if (pres) {
            std::cout << std::get<1>(activity) << ", ";
            *std::get<0>(activity) = true;
        }
        if (choix[i] == '0') {
            char z = 'a';
            while (z != 'Z') {
                bool pres;
                std::tuple<bool*, std::string>activity = getActivity(z, pres);
                if (pres) {
                    std::cout << std::get<1>(activity) << ", ";
                    setActivity(activity, pres);
                }
                if (z == 'z') {
                    z = 'A';
                    continue;
                }
                ++z;
            }
            break;
        }
        if (choix[i] == '1') {
            MISSIONS = MAIL = LOOT = FRIENDS = AGENCY = true;
            std::cout << "MISSIONS , MAIL , LOOT , FRIENDS ,  AGENCY , ";
        }  
    }
    std::cout << " will be done."<<std::endl;

}



bool game::macroEnd() {
    char z = 'a';
    while (z != 'Z') {
        bool pres;
        std::tuple<bool*, std::string>activity = getActivity(z, pres);
        if (pres) {
            if (*std::get<0>(activity))return false;
        }
        if (z == 'z') {
            z = 'A';
            continue;
        }
        ++z;
    }
    return true;
}

void game::macroLoop() {
  
    while (!endmacro) {
        switch (restartMacro) {
        case true:
            startGame();
            break;
        case false:
            goHome();
            activityLoop();
            endmacro=macroEnd();
        } 
    }
    std::cout << "End of Macro!" << std::endl;
}

void game::activityLoop()
{
    if (ADVENTURE) {
        doAdventure();
        ADVENTURE = false;
    }
    else if (ARENA) {
        doArena();
        ARENA = false;      
    }
    else if (AGENCY) {
        doAgency();
        AGENCY = false;       
    }
    else if (ALLIANCE) {
        doAlliance();
        ALLIANCE = false;       
    }
    else if (LOOT) {
        doLoot();
        LOOT = false;     
    }
    else if (MOCK) {
        doMock();
        MOCK = false;       
    }
    else if (TRIAL) {
        doTrial();
        TRIAL = false;    
    }
    else if (FRIENDS) {
        doFriends();
        FRIENDS = false;       
    }
    else if (MAIL) {
        doMail();
        MAIL = false;       
    }
    else  if (SECRETFLOOR) {
        doSecretFloor();
        SECRETFLOOR = false;        
    }
    else if (GUARDIAN) {
        doGuardian();
        GUARDIAN = false;        
    }
    else if (SHOP) {
        doShop();
        SHOP = false;        
    }
    else if (MISSIONS) {
        doMissions();
        MISSIONS = false;        
    }
    else if (TRYADVENTURE) {
        TryAdventure();
        TRYADVENTURE = false;       
    }
}



void game::startGame() {
    try {
        std::cout << "RESTART" << std::endl;
        restartMacro = false;
        rebootCount = 0;
        if (adb.onPackage(package) && goHomeFirstBoot());
        else {
            firstboot = false;
            adb.quitPackage(package);
            adb.launchPackage(activity);
            launchGame();
        }
    }
    catch (RebootException e) {
        
        return;
    }
}

void game::launchGame()
{
    try {
        std::vector<std::string>launch{ downloading,loading,okupdate,textlaunch,skipintro,netmarble,back,taptocloselaunch,nclobby,crosspopup };
        while (!fA(adventure)) {
            fcOneTemplateA(launch);
        }
    }
    catch (RebootException& e) {

        return;
    }
}


void game::goHome() {
    try {
        std::vector<std::string>home{ back,taptocloselaunch,nclobby,crosspopup };
        while (!fA(adventure)) {
            fcOneTemplateA(home);
        }   
    }
    catch (RebootException e) {
        return;
    }
}

void game::test()
{
    try {

    }
    catch (RebootException e) {
        return;
    }
}

bool game::goHomeFirstBoot() {
    try {
        if (firstboot) {
            std::cout << "First Boot of Macro and detected you're on package trying to goHome\n";
            std::cout << "Will restart if impossible\n";
            int MAXSTEPS = 7;
            firstboot = false;
            std::vector<std::string> menuelements = {adventure};
            std::vector<std::string>goback{ nclobby, crosspopup,taptocloselaunch, back };
            while (!fOneTemplateA(menuelements)) {
                while (MAXSTEPS >= 0) {
                    if (!fcOneTemplateA(goback,Zone(), 700))break;
                    else MAXSTEPS--;
                }
                if (MAXSTEPS < 0)return false;
            }
            return true;
        }
        else return false;
    }
    catch (RebootException e) {
        return false;
    }
}


void game::doMissions() {
    try {
        while (!fA(claimallmissions)) {
            fcA(missions);
        }
        while(fA(receivemissions)) {
            fcA(claimallmissions);
        }
        fcA(claimallmissions);
        while (fcA(taptoclosemissions));
        while (fcA(ncweekly));
        while (fA(receivemissions)) {
            fcA(claimallmissions);
        }
        fcA(claimallmissions);
        while (fcA(ncachievement));
        while (fA(receivemissions)) {
            fcA(claimallmissions);
        }
        fcA(claimallmissions);
    }
    catch (RebootException e) {       
        return;
    }
}

void game::doMail() {
    try {
        std::vector<std::string>allTempl{ claimallmail,mail,taptoclosemail };
        std::vector<std::string>result;
        bool claimedmail = false;
        while (true) {
            result.clear();
            if (fMultipleTemplateA(allTempl, result)) {
                if (fStr(result, mail)) {
                    if (fStr(result,claimallmail)) {
                        fcA(claimallmail);
                        claimedmail = true;
                    }
                    else fcA(mail); 
                }
                else if (fStr(result, taptoclosemail)) {
                    while(fcA(taptoclosemail));
                }
                if (claimedmail)break;
            }
        }
    }
    catch (RebootException e) {
        return;
    }
}

void game::doLoot() {
    try {
        bool alreadyClaimed = true;
        while (fA(loot)) {
            click(C.x+getMatWidth(loot), C.y - 2 * getMatHeight(loot));
        }
        while (!fcA(quickloot));
        while (fcA(quickloot));
        while (fcA(freeloot)) {
            alreadyClaimed = false;
            while (fcA(taptocloseloot));
        }
        if (alreadyClaimed) {
            while (!fcA(closeloot));
            while (fcA(closeloot));
        }
        while (!fcA(claimloot));
        while (fcA(claimloot));
        while (fcA(taptocloseloot));
        while (fcA(levelup));
    }
    catch (RebootException e) {
        return;
    }
}

void game::TryAdventure() {
    try {
        std::vector<std::string>allTempl{ adventure,adventuretile,emptyslot,focuspower,autoadventure,usetrial,autoprogress,moon };
        std::vector<std::string>res;
        std::vector<std::string>choiceadventure{ retryadventure,nextadventure };
        bool resetteam = false;
        bool dofocus = false;
        while (true) {
            res.clear();
            if (fMultipleTemplateA(allTempl, res, Zone(), 0)) {
                if (resetteam) {
                    if (fStr(res, autoadventure)) {
                        fcA(autoadventure);
                        continue;
                    }
                    if (dofocus) {
                        if (fStr(res, focuspower)) {
                            if (fcA(focuspower)) {
                                dofocus = false;
                            }
                            continue;
                        }
                    }
                    else if (fStr(res, usetrial)) {
                        if (fcA(usetrial)) {
                            resetteam = false;
                        }
                        continue;
                    }
                }
                if (fOneStr(res, { adventure,adventuretile })) {
                    fcOneTemplateA({ adventure,adventuretile });
                }
                else if (fStr(res, moon)) {
                    while (fcA(moon));
                    break;
                }
                else if (fStr(res, autoprogress)) {
                    if (fStr(res, emptyslot)) {
                        resetteam = true;
                        dofocus = true;
                    }
                    else fcOneTemplateA({ okadventure,autoprogress });
                }
            }
        }
    }
    catch (RebootException e) {       
        return;
    }
}

void game::doAdventure() {
    try {
        std::vector<std::string>allTempl{adventure,adventuretile,pausebattle,nextteam,emptyslot,focuspower,autoadventure,usetrial,enterbattleadventure,retryadventure,nextadventure };
        std::vector<std::string>res;
        std::vector<std::string>choiceadventure{ retryadventure,nextadventure };
        bool resetteam=false;
        bool dofocus = false;
        while (true) {
            res.clear();
            if (fMultipleTemplateA(allTempl, res, Zone(), 0)) {
                if (resetteam) {
                    if (fStr(res, autoadventure)) {
                        fcA(autoadventure);
                        continue;
                    }
                    if (dofocus) {
                        if (fStr(res, focuspower)) {
                            if (fcA(focuspower)) {
                                dofocus = false;
                            }
                            continue;
                        }
                    }
                    else if (fStr(res, usetrial)) {
                        if (fcA(usetrial)) {
                            resetteam = false;
                        }
                        continue;
                    }
                }
                if (fOneStr(res, { adventure,adventuretile })) {
                    fcOneTemplateA({ adventure,adventuretile });
                }
                else if (fStr(res, pausebattle)) {
                    while (fA(pausebattle));
                }
                else if (fStr(res, enterbattleadventure)) {
                    if (fStr(res, emptyslot)) {
                        resetteam = true;
                        dofocus = true;
                    }
                    else while (fcOneTemplateA({ okadventure,enterbattleadventure }));
                }
                else if (fStr(res, nextteam)) {
                    if (fStr(res, emptyslot)) {
                        resetteam = true;
                        dofocus = true;
                    }
                    else while (fcA(nextteam));
                }
                else if (fOneStr(res, choiceadventure)) {
                    break;
                }
            }
        }
        while (!fA(adventure)) {
            fcOneTemplateA({ okleaveadventure,back });
        }
    }
    catch (RebootException e) {       
        return;
    }
}

void game::doFriends() {
    try {
        while (!fA(sendall)) {
            fcA(friends);
        }
        while (!fA(blueheart));    
        fcA(sendall);
        fcA(receiveall);
    }
    catch (RebootException e) {       
        return;
    }
}

void game::doShop() {
    try {
        std::vector<std::string>gotodaily{cdailyshop,ncdailyshop, ncbundle };
        while (!fA(ncbundle)) {
            fcA(shop);
        }
        while (!fA(ondailyshop)) {
            fcOneTemplateA(gotodaily);
        }
        fcA(freepack);
        while (fcA(taptocloseshop));
        while (!fA(onweeklyshop)) {
            fcA(ncweeklyshop);
        }
        fcA(noweeklyfreepack);
        while (fcA(taptocloseshop));
        while (!fSwipeA(cweeklyshop,leftx, samey));
        while (!fA(ncmonthlyshop)) {
            fSwipeA(cweeklyshop, leftx, samey);
        }
        while (!fA(onmonthlyshop)) {
            fcA(ncmonthlyshop);
        }
        fcA(nomonthlyfreepack);//add monthlyfreepack
        while (fcA(taptocloseshop));
        while (fcA(ncseasonpass));
        while (!fcA(claimallmissions));
        while (fcA(taptocloseshop));
        while (fcA(ncconquestpass));
        while (!fcA(claimallmissions));
        while (fcA(taptocloseshop));
        while (fcA(ncundergroundpass));
        while (!fcA(claimallmissions));
        while (fcA(taptocloseshop));
        while (!fSwipeA(cundergroundpass, leftx, samey));
        while (!fA(ncignitionpass)) {
            fSwipeA(cundergroundpass, leftx, samey);
        }
        while (fcA(ncignitionpass));
        while (!fcA(claimallmissions));
        while (fcA(taptocloseshop));
    }
    catch (RebootException e) {       
        return;
    }
}

void game::doArena() {
    try {
        bool nomore = false;
        int noranker = 0;

        while (!fA(arena)) {
            fcA(ncexpedition);
        }
        std::vector<std::string>choiceenter{ arena,regulararena };
        while (!fA(challengearena)) {
            fcOneTemplateA(choiceenter);
        }
        std::vector<std::string>arenastart{ challengearena,vsquickresult, };
        std::vector<std::string>entercombat{ okadventure,quickresultarena, };
        bool resetteam = true;
        while (true) {
            while (!fcA(resetopponentarena)) {
                fcOneTemplateA(arenastart);
            }
            swipeY(dimY * 0.6, dimY * 0.3,500);
            swipeY(dimY * 0.6, dimY * 0.3,500);
            if (!fA(freearena))break;
            while (fcOneTemplateMultipleTemplateA(freearena, S, 1));
            while (!fA(focuselement)) {
                fcA(autoadventure);
            }
            while (!fA(autoadventure)) {
                fcA(focuselement);
                while (fcA(usetrial));
            }
            resetteam = false;   
            while (fcOneTemplateA(entercombat));
        }
    }
    catch (RebootException e) {       
        return;
    }
}




void game::doMock() {
    try {
        std::vector<std::string>startmock{ noattempts,challengemock, };
        std::vector<std::string>gotomock{ mockbattle, mock, ncexpedition };

        std::string result;
        while (!fOneTemplateA(startmock, result)) {
            fcOneTemplateA(gotomock);
        }
        if (result==challengemock) {
            while (fcA(challengemock));
            while (true) {
                while (!fA(completemock)) {
                    fcA(enterbattlemock);
                    fA(pausebattle);
                }
                if (!fA(start2ndmock))break;
                while (fcA(start2ndmock));
            }
        }   
        std::vector<std::string>leavemock{mock, back };
        std::vector<std::string>gotounderground{undergroundlab,mock, back };
        while (!fA(undergroundlab)) {
            fcOneTemplateA(leavemock);
        }
        while (!fOneTemplateA(startmock,result)) {
            fcOneTemplateA(gotounderground);
        }
        if (result == challengemock) {
            while (fcA(challengemock));
            while (!fA(completemock)) {
                fcA(enterbattlemock);
                fA(pausebattle);
            }     
        }
    }
    catch (RebootException e) {       
        return;
    }
}

void game::doTrial() {
    try {
        std::vector<std::string>listcolor;
        switch (getUTCDay()) {
            case Monday:
                listcolor.push_back(yellowtrial);
                while (fcA(yellowtrial));
                break;        
            case Tuesday:
                listcolor.push_back(purpletrial);
                while (fcA(purpletrial));
                break;        
            case Wednesday:
                listcolor.push_back(redtrial);
                while (fcA(redtrial));
                break;        
            case Thursday:
                listcolor.push_back(bluetrial);
                while (fcA(bluetrial));
                break;        
            case Friday:
                listcolor.push_back(greentrial);
                while (fcA(greentrial));
                break;        
            default:
                listcolor = { yellowtrial, purpletrial, redtrial, bluetrial, greentrial };
                break;
        }
        for(std::string trycolor : listcolor){
            while (!fA(trialofchaos)) {
                fcOneTemplateA({ ncexpedition, trial,back });
            }
            while (!fA(challengetrial)) {
                fcA(trycolor);
            }
            std::vector<std::string> choicetrial{ okadventure, enterbattletrial };
            std::vector<std::string> allTempl{ battlestatstrial,enterbattletrial,nexttrial,challengetrial,pausebattle,limitedtrial,autoadventure,usetrial,focuspower,emptyslot };
            std::vector<std::string> resall;
            bool nochallenges = false;
            bool resetteam = true;
            bool actualize = false;
            bool selectedfocus = false;
            bool selectedauto = false;
            int nbtries = 0;
            while (true) {
                resall.clear();
                if (fMultipleTemplateA(allTempl, resall,Zone(),0)) {
                    if (resetteam) {   
                        if (fStr(resall, autoadventure)) {
                            fcA(autoadventure);
                            continue;
                        }
                        if (!selectedfocus) {
                            if (fStr(resall, focuspower)) {
                                if (fcA(focuspower)) {
                                    selectedfocus = true;
                                }
                                continue;
                            }
                        }
                        else if (fStr(resall, usetrial)) {
                            if (fcA(usetrial)) {
                                resetteam = false;
                            }
                            continue;
                        }
                    }
                    if (fStr(resall, challengetrial)) {
                        if(fStr(resall, limitedtrial)){
                            std::cout << "No more tries\n";
                            break;
                        }
                        else if (nbtries < 8) {
                            fcA(challengetrial, Zone(),0);
                            nbtries++;
                        }
                        else {
                            std::cout << "No more tries\n";
                            break;
                        }
                    }
                    else if (fStr(resall, enterbattletrial)) {
                        nbtries = 0;
                        if (fStr(resall, emptyslot)) {
                            std::cout << "Detected Empty Slot\n";
                            resetteam = true;
                            selectedfocus = false;
                        }
                        else while(fcOneTemplateA(choicetrial));
                    }
                    else if (fStr(resall, pausebattle)) {
                        while (fA(pausebattle));
                    }
                    else if (fStr(resall,battlestatstrial)) {
                        if (fStr(resall, nexttrial)) {
                            fcA(nexttrial);
                            nbtries++;
                        }
                        else if (actualize) {
                            std::cout << "No more tries\n";
                            break;              
                        }
                        else actualize = true;
                    }
                }
            }  
        }       
    }
    catch (RebootException e) {       
        return;
    }
}

void game::doAgency() {
    try {
        while (!fA(agency)) {
            fcA(nccontrolcenter);
        }
        while (!fA(onagency)) {
            fcA(agency);
        }
        while (!fcA(claimallagency)) {
            fcA(taptocloseagency);
        }
        while (!fcA(claimallagency)) {
            fcA(taptocloseagency);
        }
        while (!fcA(progressallagency));
        while (!fcA(progressallagency));
        while (fcA(nccoop));
        while (!fcA(claimallagency)) {
            fcA(taptocloseagency);
        }        while (!fcA(claimallagency)) {
            fcA(taptocloseagency);
        }
        while (!fcA(progressallagency));
        while (!fcA(progressallagency));
    }
    catch (RebootException e) {       
        return;
    }
}

void game::doAlliance() {
    try {
        while (!fA(alliance)) {
            fcA(nccontrolcenter);
        }
        std::vector<std::string>alliancechoice{ checkin,alliance };
        while (!fA(checkintile)) {
            fcOneTemplateA(alliancechoice);
        }
        while (fcCompareA(checkintile, nocheckintile));
    }
    catch (RebootException e) {       
        return;
    }
}

void game::doGuardian()
{
    try {
        while (!fA(guardian)) {
            fcA(ncexpedition);
        }
        bool resetteam = true;
        bool enemytofight = false;
        std::vector<std::string> enterguardian{ taptoclosemail,guardian };
        std::vector<std::string> choosestars{ threeemptystars, oneoutofthreestars};
        std::vector<std::string> alreadychallenged{ twooutofthreestars, threefullstars };
        std::vector<std::string> entercombat{ okadventure, enterbattleadventure };
        std::vector<std::string> endlist{ threeemptystars, oneoutofthreestars,guardianlock,bottomguardian };
        std::vector<std::string> reslist;
        Zone toObserve;
        while (!fA(dayguardian)) {
            fcOneTemplateA(enterguardian);
        }
        while (fcA(taptoclosemail));
        fOneTemplateMultipleTemplateA(dayguardian, N, 0);
        for (int i = 0; i < 3; ++i) {
            swipeY(C.y, dimY - dimY / 10, 500);
        }
        while (true){
            reslist.clear();
            if (fMultipleCompareTemplateA(endlist, alreadychallenged, reslist)) {
                if (fOneStr(reslist, choosestars)) {
                    if (fStr(reslist, guardianlock)) {
                        fOneTemplateMultipleTemplateA(guardianlock, N, 0);
                        toObserve = { Coords(0, 0), Coords(dimX, C.y - getMatHeight(guardianlock)) };
                        if (fCompareOneTemplateMultipleTemplateA(choosestars, alreadychallenged, N, 0, toObserve))enemytofight = true;
                        break;
                    }
                    else if (fStr(reslist, bottomguardian)) {
                        if (fCompareOneTemplateMultipleTemplateA(choosestars, alreadychallenged, N, 0))enemytofight = true;
                        break;
                    }
                    else {
                        if (fCompareOneTemplateMultipleTemplateA(choosestars, alreadychallenged, N, 0)) {
                            enemytofight = true;
                            break;
                        }
                    }
                }
            }
            else swipeY(dimY-1, dimY/1.5f,1500);
        }

        if (enemytofight) {
            while (!fA(challengeguardian)) {
                fcCompareOneTemplateMultipleTemplateA(choosestars, alreadychallenged, N, 0);
            }
            std::vector<std::string>allTempl{autoadventure,focuspower, pausebattle,challengeguardian,enterbattleadventure,nexttest,nonextchallenge,emptyslot,usetrial };
            std::vector<std::string>res;
            int gardeFou = 0;
            bool selectedfocus = false;
            bool endguardian = false;
            while (true) {
                res.clear();
                if (fMultipleTemplateA(allTempl, res,Zone(),0)) {
                    if (resetteam) {
                        if (fStr(res, autoadventure)) {
                            fcA(autoadventure);
                            continue;
                        }
                        if (!selectedfocus) {
                            if (fStr(res, focuspower)) {
                                if (fcA(focuspower)) {
                                    selectedfocus = true;
                                }
                                continue;
                            }
                        }
                        else if (fStr(res, usetrial)) {
                            if (fcA(usetrial)) {
                                resetteam = false;
                            }
                            continue;
                        }
                    }
                    if (fStr(res, challengeguardian)) {
                        gardeFou = 0;
                        while (fcA(challengeguardian));
                    }
                    else if (fStr(res, nexttest)) {
                        if (fStr(res, nonextchallenge)) {
                            std::cout << "No Next challenge !\n";
                            break;
                        }
                        else if(gardeFou<10){
                            fcA(nexttest, Zone(), 0);
                            gardeFou++;
                        }
                        else {
                            std::cout << "Didn't detect challengeGuardian after 10 times, No next Challenge\n";
                            break;
                        }
                    }
                    else if (fStr(res,pausebattle)) {
                        while (fA(pausebattle));
                    }
                    else if (fStr(res, enterbattleadventure)) {
                        if (fStr(res, emptyslot)) {
                            std::cout << "Empty Slot Detected\n";
                            selectedfocus = false;
                            resetteam = true;
                        }
                        else while(fcOneTemplateA(entercombat));
                    }
                }
            }      
        }
    }
    catch (RebootException e) {
        return;
    }
}

void game::doSecretFloor()
{
    try {
        while (!fA(secretfloor)) {
            fcA(ncexpedition);
        }
        while (!fA(secretfloorfirstboss)) {
            fcA(secretfloor);
        }
        std::string choice;
        std::vector<std::string>clear{ notfreeautoclear,freeautoclear};
        std::vector<std::string>sweep{ taptoclosemail,freeautoclear };
        while (!fOneTemplateA(clear,choice)) {
            fcA(secretfloorfirstboss);
        }
        if (choice == freeautoclear) {
            if (fCompareA(freeautoclear, noautoclear)) {
                while (!fA(notfreeautoclear)) {
                    if (fA(onautoclear)) {
                        fcA(autoclear);
                    }
                    else fcOneTemplateA(sweep);
                }
            }
        }

    }
    catch (RebootException e) {
        return;
    }
}







void game::setAdb(fadb adb) {
    this->adb = adb;
}

void game::startMacro()
{
    mac.setDim(dimX, dimY);
    mac.initMacroConfig();
    initActivities();
    selectActivity();
    sys.createpaths(templates);
    mac.blue.startInstance(mac.playingInstance);
    mac.updateBlueStacksConfAdbPort(mac.playingInstance);
    adb.setPort(mac.playingInstance.port);
    adb.devices();
    adb.disconnectLocalhost(adb.intport);
    adb.connectLocalhost(adb.intport);
    sys.setPort(adb.intport);
    loadAllTemplates();
}
void game::setSys(sysCommands sys) {
    this->sys = sys;
}
int game::getDimX() {
    return dimX;
}

int game::getDimY() {
    return dimY;
}

void game::setPort(int port) {
    adb.setPort(port);
}

day game::getUTCDay() {
    auto now = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(now);
    tm utc_time;
    gmtime_s(&utc_time, &current_time);
    int day = utc_time.tm_wday;
    switch (day) {
    case 0:
        return Sunday;
    case 1:
        return Monday;
    case 2:
        return Tuesday;
    case 3:
        return Wednesday;
    case 4:
        return Thursday;
    case 5:
        return Friday;
    case 6:
        return Saturday;
    default:
        return Monday;
    }
}

int game::getUTCHour() {
    auto now = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(now);
    tm utc_time;
    gmtime_s(&utc_time, &current_time);
    return utc_time.tm_hour;
}

std::tuple<bool*, std::string> game::getActivity(char key, bool& present)
{
    if (allActivities.find(key) != allActivities.end()) {
        present = true;
        return allActivities.at(key);

    }
    present = false;
    return std::tuple<bool*, std::string>();
}

void game::setActivity(char key, bool activate)
{
    bool found = false;
    std::tuple<bool*, std::string>activity = getActivity(key, found);
    if (found) {
        *std::get<0>(activity) = activate;
    }
}

void game::setActivity(std::tuple<bool*, std::string> tuple, bool activate)
{
    *std::get<0>(tuple) = activate;
}



void game::loadTemplate(std::string image)
{
    Template newTemplate(image);
    allTemplates.insert(std::pair<std::string, Template>(image, newTemplate));
}

void game::loadAllTemplates() {
    std::string path = ".\\assets\\templates";
    std::filesystem::directory_iterator dir(path);
    std::vector<std::string>allFileNames;
    getFilesPath(allFileNames, dir);
    for (const std::string str : allFileNames) {
        loadTemplate(str);
    }
}

void game::getFilesPath(std::vector<std::string>& tab, std::filesystem::directory_iterator path)
{
    std::filesystem::path currentPath = path->path().parent_path();

    std::vector<std::filesystem::directory_entry> folders;
    folders.clear();
    for (const auto& entry : path) {
        if (entry.is_regular_file()) {
            tab.push_back(entry.path().string());
        }
        else if (entry.is_directory()) {
            folders.push_back(entry);
        }
    }
    for (int i = 0; i < folders.size(); i++) {
        if (!std::filesystem::is_empty(folders.at(i).path())) {
            getFilesPath(tab, std::filesystem::directory_iterator(folders.at(i).path()));
        }
        else {
            std::filesystem::path currentPath = folders.at(i).path();
        }
    }
}

void game::showVector(std::vector<std::string> vect)
{
    for (auto str : vect) {
        std::cout << str << "\n";
    }
}

Template game::getTemplate(std::string image, typeMat type) {
    if (allTemplates.find(image) != allTemplates.end()) {
        Template templ = allTemplates.at(image);
        templ.setType(type);
        return templ;
    }
    else return Template();
}

std::vector<Template> game::getTemplate(std::vector<std::string> images, typeMat type)
{
    std::vector<Template> result;
    for (std::string image : images) {
        if (allTemplates.find(image) != allTemplates.end()) {
            Template templ = allTemplates.at(image);
            templ.setType(type);
            result.push_back(templ);
        }
    }
    return result;
}


int game::getYear() {
    std::time_t t = std::time(nullptr);
    std::tm now;
    localtime_s(&now, &t);
    return now.tm_year + 1900;
}

int game::getMonth() {
    std::time_t t = std::time(nullptr);
    std::tm now;
    localtime_s(&now, &t);
    return now.tm_mon + 1;
}

int game::getDay() {
    std::time_t t = std::time(nullptr);
    std::tm now;
    localtime_s(&now, &t);
    int dayOfWeek = now.tm_wday;
    if (dayOfWeek == 0) {
        dayOfWeek = 7;
    }
    return dayOfWeek;
}

int game::getHour() {
    std::time_t t = std::time(nullptr);
    std::tm now;
    localtime_s(&now, &t);
    return now.tm_hour;
}

int game::getMinute() {
    std::time_t t = std::time(nullptr);
    std::tm now;
    localtime_s(&now, &t);
    return now.tm_min;
}

int game::getSecond() {
    std::time_t t = std::time(nullptr);
    std::tm now;
    localtime_s(&now, &t);
    return now.tm_sec;
}

int game::getCx()const {
    return C.x;
}

int game::getCy()const {
    return C.y;
}

void game::setRebootCount(int nb) {
    rebootCount = nb;
}

int game::getRebootCount() {
    return rebootCount;
}

void game::setDimX(int x) {
    dimX = x;
}
void game::setDimY(int y) {
    dimY = y;
}
int game::getMatWidth(const std::string& name)
{
    return op.CreateMat(name, Gray).cols;
}
int game::getMatHeight(const std::string& name)
{
    return op.CreateMat(name, Gray).rows;
}

void game::wait(int milliSeconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliSeconds));
}
void game::swipeX(int x1, int x2, int millitime)
{
    swipe(x1, dimY / 2, x2, dimY / 2, millitime);
}

void game::swipeY(int y1, int y2, int millitime)
{
    swipe(dimX / 2, y1, dimX / 2, y2, millitime);
}

void game::swipe(int x1, int y1, int x2, int y2, int millitime)
{
    adb.swipe(x1, y1, x2, y2, millitime);
}

void game::click(Coords Coord)
{
    adb.touch(Coord.x, Coord.y);
}
void game::click(int x,int y)
{
    adb.touch(x, y);
}

void game::orderDigits(std::vector<Digit>& digits) {
    std::sort(digits.begin(), digits.end(), [&](const Digit& a, const Digit& b) {
        return a.Cnb.x < b.Cnb.x;
        });
}

bool game::eraseString(std::vector<std::string>& allTempl, std::string templ)
{
    std::vector<std::string>::iterator it;
    it = std::find(allTempl.begin(), allTempl.end(), templ);
    if (it!=allTempl.end()) {
        allTempl.erase(it);
        return true;
    }
    return false;
}

bool game::fStr(const std::vector<std::string>& allTempl, std::string templ)
{
    std::vector<std::string>::iterator it;
    return std::find(allTempl.begin(), allTempl.end(), templ) != allTempl.end();
}

bool game::fStr(const std::vector<std::string>& allTempl, const std::vector<std::string> allkeys)
{
    for (std::string key : allkeys) {
        if(!fStr(allTempl,key))return false;
    }
    return true;
}

bool game::fOneStr(const std::vector<std::string>& allTempl, const std::vector<std::string> allkeys)
{
    for (std::string key : allkeys) {
        if (fStr(allTempl, key))return true;
    }
    return false;
}


int game::distancePoint(const Coords& fixpt, const Coords& pt)
{
    return (int)sqrt(pow(fixpt.x - pt.x, 2) + pow(fixpt.y - pt.y, 2));
}

std::vector<Coords> game::orderCoords(const std::vector<Coords>& coordes, pos dir) {
    std::vector<Coords> coords = coordes;

    switch (dir) {
    case N:
        std::sort(coords.begin(), coords.end(), [](const Coords& a, const Coords& b) {
            return a.y < b.y;
            });
        break;

    case S:
        std::sort(coords.begin(), coords.end(), [](const Coords& a, const Coords& b) {
            return a.y > b.y;
            });
        break;

    case W:
        std::sort(coords.begin(), coords.end(), [](const Coords& a, const Coords& b) {
            return a.x < b.x;
            });
        break;

    case E:
        std::sort(coords.begin(), coords.end(), [](const Coords& a, const Coords& b) {
            return a.x > b.x;
            });
        break;

    case NW:
        std::sort(coords.begin(), coords.end(), [](const Coords& a, const Coords& b) {
            return a.x + a.y < b.x + b.y;
            });
        break;

    case NE:
        std::sort(coords.begin(), coords.end(), [](const Coords& a, const Coords& b) {
            return a.x - a.y > b.x - b.y;
            });
        break;

    case SW:
        std::sort(coords.begin(), coords.end(), [](const Coords& a, const Coords& b) {
            return a.y - a.x > b.y - b.x;
            });
        break;

    case SE:
        std::sort(coords.begin(), coords.end(), [](const Coords& a, const Coords& b) {
            return a.x + a.y > b.x + b.y;
            });
        break;
    }


    return coords;
}

std::vector<Template> game::orderTemplates(const std::vector<Template>& allTempl, pos dir) {
    std::vector<Template> coords = allTempl;

    switch (dir) {
    case N:
        std::sort(coords.begin(), coords.end(), [](const Template& a, const Template& b) {
            return a.C.y < b.C.y;
            });
        break;

    case S:
        std::sort(coords.begin(), coords.end(), [](const Template& a, const Template& b) {
            return a.C.y > b.C.y;
            });
        break;

    case W:
        std::sort(coords.begin(), coords.end(), [](const Template& a, const Template& b) {
            return a.C.x < b.C.x;
            });
        break;

    case E:
        std::sort(coords.begin(), coords.end(), [](const Template& a, const Template& b) {
            return a.C.x > b.C.x;
            });
        break;

    case NW:
        std::sort(coords.begin(), coords.end(), [](const Template& a, const Template& b) {
            return a.C.x + a.C.y < b.C.x + b.C.y;
            });
        break;

    case NE:
        std::sort(coords.begin(), coords.end(), [](const Template& a, const Template& b) {
            return a.C.x - a.C.y > b.C.x - b.C.y;
            });
        break;

    case SW:
        std::sort(coords.begin(), coords.end(), [](const Template& a, const Template& b) {
            return a.C.y - a.C.x > b.C.y - b.C.x;
            });
        break;

    case SE:
        std::sort(coords.begin(), coords.end(), [](const Template& a, const Template& b) {
            return a.C.x + a.C.y > b.C.x + b.C.y;
            });
        break;
    }


    return coords;
}

std::vector<Coords> game::orderPoint(const std::vector<Coords>& coords, const Coords& Cf)
{
    std::vector<Coords> newcoords = coords;
    std::sort(newcoords.begin(), newcoords.end(), [&](const Coords& a, const Coords& b) {
        int distanceA = distancePoint(a, Cf);
        int distanceB = distancePoint(b, Cf);
        return distanceA < distanceB;
        });
    return newcoords;
}

void game::fillPopup()
{
    std::vector<std::string> discpopup = { };
    std::vector<std::string> blockpopup = { retryconnect};
    for (std::string discstr : discpopup) {
        Popup P(discstr, state::disconnect);
        listPopup.push_back(P);
    }
    for (std::string blockstr : blockpopup) {
        Popup P(blockstr, state::block);
        listPopup.push_back(P);
    }
}



bool game::fcA(const std::string& templ, Zone Z, unsigned int delayMilliseconds) {
    return fA(templ,Z, delayMilliseconds, true);
}

bool game::fA(const std::string& templ, Zone Z, unsigned int delayMilliseconds, bool willInteract) {
    bool found = false;
    resetCount();
    Template Mat = getTemplate(templ);
    Template Tresult;
    loopPopUp(Mat.type);
    if (op.cvmtfTemplate(Mat, background, Tresult,Z))found = true;
    return templateFound(found,Tresult, willInteract, delayMilliseconds);
}

bool game::fcpopupA()
{
    Template bmat(backg, Gray);
    for (Popup pop: listPopup) {
        Template Tresult;
        if (op.cvmtfTemplate(pop, bmat,Tresult)) {
            state cond = pop.action;
            switch (cond) {
            case state::block:
                click(Tresult.C);
                wait(DEFAULTDELAY);
                return true;
                break;

            case state::disconnect:
                restartMacro = true;
                throw RebootException();
                break;
            }
        }

    }
    return false;
}

void game::loopPopUp(typeMat color)
{
    do {
        adb.screenshot();
        background.mat = op.CreateMat(backg, Color);
        background.graymat = op.CreateMat(backg, Gray);
        background.type = color;
    } while (fcpopupA());
}


bool game::fcOneTemplateMultipleTemplateA(const std::string& templ, pos direction, int order,Zone Z, unsigned int delayMilliseconds) {
    return fOneTemplateMultipleTemplateA(templ, direction, order,Z, delayMilliseconds, true);
}

bool game::fOneTemplateMultipleTemplateA(const std::string& templ, pos direction, int order,Zone Z, unsigned int delayMilliseconds, bool willInteract) {

    bool found = false;
    resetCount();
    std::vector<Template>Tresults;
 
    Template Tresult = getTemplate(templ);
    loopPopUp(Tresult.type);
    if (op.cvmtfMultipleTemplate(Tresult, background, Tresults,Z)) {
        found = true;
        Tresults = orderTemplates(Tresults, direction);
        if (order < 0)order = 0;
        if (order >= Tresults.size())order = Tresults.size() - 1;
        Tresult = Tresults.at(order);
    }
    return templateFound(found, Tresult, willInteract, delayMilliseconds);
}


bool game::fCompareOneTemplateMultipleTemplateA(const std::vector<std::string>& alltempl, const std::vector<std::string>& simTempl, pos direction, int order,Zone Z, unsigned int delayMilliseconds, bool willInteract)
{
    bool found = false;
    resetCount();

    std::vector<Template>Tresults;
    std::vector<Template>allMats = getTemplate(alltempl,Color);
    std::vector<Template>simMats = getTemplate(simTempl,Color);
    Template Tresult;
    loopPopUp(Color);
    if (op.cvmtfMultipleTemplateCompareMultipleTemplate(allMats, background, simMats, Tresults,Z)) {
        found = true;
        Tresults = orderTemplates(Tresults, direction);
        if (order < 0)order = 0;
        if (order >= Tresults.size())order = Tresults.size() - 1;
        Tresult = Tresults.at(order);
    }
    return templateFound(found, Tresult, willInteract, delayMilliseconds);
}

bool game::fcCompareOneTemplateMultipleTemplateA(const std::vector<std::string>& alltempl, const std::vector<std::string>& simTempl, pos direction, int order,Zone Z, unsigned int delayMilliseconds)
{
    return fCompareOneTemplateMultipleTemplateA(alltempl, simTempl, direction, order,Z, delayMilliseconds, true);
}


bool game::fOneTemplateMultipleTemplateA(const std::vector<std::string>& alltempl, const pos& direction, int order, Zone Z, unsigned int delayMilliseconds, bool willInteract)
{
    bool found = false;
    resetCount();

    std::vector<Template>Tresults;
    std::vector<Template>allMats = getTemplate(alltempl);
    Template Tresult;
    loopPopUp();
    if (op.cvmtfMultipleTemplate(allMats, background, Tresults, Z)) {
        found = true;
        Tresults = orderTemplates(Tresults, direction);
        if (order < 0)order = 0;
        if (order >= Tresults.size())order = Tresults.size() - 1;
        Tresult = Tresults.at(order);
    }
    return templateFound(found, Tresult, willInteract, delayMilliseconds);
}

bool game::fcOneTemplateMultipleTemplateA(const std::vector<std::string>& alltempl, const pos& direction, int order, Zone Z, unsigned int delayMilliseconds)
{
    return fOneTemplateMultipleTemplateA(alltempl, direction, order, Z, delayMilliseconds, true);
}

bool game::fnbTemplateA(const std::string& templ, int& nb,Zone Z, unsigned int delayMillisecond, bool willInteract)
{
    bool found = false;
    resetCount();
    std::vector<Template>Tresult;
    nb = 0;
    Template Templ = getTemplate(templ);
    loopPopUp();
    if (op.cvmtfMultipleTemplate(Templ, background, Tresult,Z)) {
        found = true;
        nb = Tresult.size();
    }
    return found;
}

int game::fnbTemplateA(const std::string& templ, Zone Z, unsigned int delayMilliseconds, bool willInteract)
{
    resetCount();
    bool found = false;
    std::vector<Template>Tresult;
    Template Templ = getTemplate(templ);
    loopPopUp();
    if (op.cvmtfMultipleTemplate(Templ, background, Tresult, Z)) {
        found = true;
    }
    templateFound(found, Template(), willInteract, delayMilliseconds);
    return Tresult.size();
}

int game::fnbTemplateA(const std::vector<std::string>& allTempl, Zone Z, unsigned int delayMilliseconds, bool willInteract)
{
    resetCount();
    bool found = false;
    std::vector<Template>Tresult;
    std::vector<Template> Templ = getTemplate(allTempl);
    loopPopUp();
    if (op.cvmtfMultipleTemplate(Templ, background, Tresult, Z)) {
        found = true;
    }
    templateFound(found, Template(), willInteract, delayMilliseconds);
    return Tresult.size();
}

int game::fnbMultipleCompareTemplateA(const std::vector<std::string>& allTempl, const std::vector<std::string>& simTempls, Zone Z, unsigned int delayMilliseconds, bool willInteract)
{
    resetCount(); 
    bool found = false;
    std::vector<Template>Tresult;
    std::vector<Template> Templ = getTemplate(allTempl,Color);
    std::vector<Template> simTemplates = getTemplate(simTempls,Color);
    loopPopUp(Color);
    if (op.cvmtfMultipleTemplateCompareMultipleTemplate(Templ, background, simTemplates, Tresult, Z)) {
        found = true;
    }
    templateFound(found, Template(), willInteract, delayMilliseconds);
    return Tresult.size();
}

int game::fnbUniqueCompareTemplateA(const std::vector<std::string>& allTempl, const std::vector<std::string>& simTempls, Zone Z, unsigned int delayMilliseconds, bool willInteract)
{
    resetCount();
    bool found = false;
    std::vector<Template>Tresult;
    std::vector<Template> Templ = getTemplate(allTempl,Color);
    std::vector<Template> simTemplates = getTemplate(simTempls,Color);
    std::vector<std::string> tid;
    loopPopUp(Color);
    if (op.cvmtfMultipleTemplateCompareMultipleTemplate(Templ, background, simTemplates, Tresult, Z)) {
        found = true;
        for (Template t : Tresult) {
            tid.push_back(t.id);
        }
        auto last = std::unique(tid.begin(), tid.end());
        tid.erase(last, tid.end());

    }
    templateFound(found, Template(), willInteract, delayMilliseconds);
    return tid.size();
}

int game::fnbCompareTemplateA(const std::string& templ, const std::vector<std::string>& simTempls, Zone Z, unsigned int delayMilliseconds, bool willInteract)
{
    resetCount();
    bool found = false;
    std::vector<Template>Tresult;
    Template Templ = getTemplate(templ,Color);
    std::vector<Template> simTempl = getTemplate(simTempls,Color);
    loopPopUp(Color);
    if (op.cvmtfMultipleTemplateCompareMultipleTemplate(Templ, background, simTempl, Tresult, Z)) {
        found = true;
    }
    templateFound(found, Template(), willInteract, delayMilliseconds);
    return Tresult.size();
}

bool game::fcCompareA(const std::string& goodTemplate, const std::string& similartemplate,Zone Z, unsigned int delayMilliseconds)
{
    return fCompareA(goodTemplate, similartemplate,Z, delayMilliseconds, true);
}

bool game::fCompareA(const std::string& goodTemplate, const std::string& similartemplate,Zone Z, unsigned int delayMilliseconds, bool willInteract)
{
    bool found = false;
    resetCount();
    Template Tresult;
    Template goodmat = getTemplate(goodTemplate, Color);
    Template smat = getTemplate(similartemplate, Color);
    loopPopUp(goodmat.type);
    if (op.cvmtfCompareTemplate(goodmat, background, smat, Tresult,Z))found = true;
    return templateFound(found, Tresult, willInteract, delayMilliseconds);
}


bool game::fcCompareMultipleTemplateA(const std::string& goodTemplate, const std::vector<std::string>& similartemplates, Zone Z, unsigned int delayMillisesconds)
{
    return fCompareMultipleTemplateA(goodTemplate, similartemplates,Z,delayMillisesconds, true);
}

bool game::fCompareMultipleTemplateA(const std::string& goodTemplate, const std::vector<std::string>& similartemplates,Zone Z, unsigned int delayMilliseconds, bool willInteract)
{
    bool found = false;
    resetCount();
    Template Tresult;
    Template goodmat = getTemplate(goodTemplate, Color);
    std::vector<Template>simMats=getTemplate(similartemplates,Color);
    loopPopUp(goodmat.type);
    if (op.cvmtfCompareMultipleTemplate(goodmat, background, simMats, Tresult))found = true;
    return templateFound(found, Tresult, willInteract, delayMilliseconds);
}


bool game::fMultipleCompareMultipleTemplateA(const std::string& goodTemplate, const std::vector<std::string>& similartemplates, Zone Z, unsigned int delayMilliseconds, bool willInteract)
{
    bool found = false;
    resetCount();
    std::vector<Template>Tresult;
    Template goodmat = getTemplate(goodTemplate, Color);
    std::vector<Template>simMats = getTemplate(similartemplates, Color);
    loopPopUp(goodmat.type);

    if (op.cvmtfMultipleTemplateCompareMultipleTemplate(goodmat, background, simMats, Tresult,Z))found = true;
    return templateFound(found, goodmat, willInteract, delayMilliseconds);
}


bool game::templateFound(bool found,const Template&templ, bool willInteract, unsigned int delayMilliseconds)
{
    if (found) {
        rebootCount = 0;
        C = templ.C;
        int width=templ.width;
        int height=templ.height;
        int randomXOffset = rand() % ((width / 2)+1);
        int randomYOffset = rand() % ((height / 2)+1);
        int randomX = C.x + randomXOffset+1;
        int randomY = C.y + randomYOffset+1;

        if (willInteract) {
            click(randomX, randomY);
        }
        if (delayMilliseconds == DEFAULTDELAY) {
            wait(waitfound);
        }
        else wait(delayMilliseconds);
    }
    else {
        rebootCount++;
        if (delayMilliseconds == DEFAULTDELAY) {
            wait(waitnotfound);
        }
        else wait(delayMilliseconds);
    }
    return found;
}

void game::resetCount() {
    if (rebootCount >= MAXREBOOT) {
        std::cout << "Rebooting\n" << std::endl;
        restartMacro = true;
        throw RebootException();
    }
}


bool game::templateFound(bool found, const Template& templ, bool willInteract, Action act, Coords coord , unsigned int delayMilliseconds)
{
    if (found) {
        rebootCount = 0;
        C = templ.C;
        int width = templ.width;
        int height = templ.height;
        int randomXOffset = rand() % (width / 2)+1;
        int randomYOffset = rand() % (height / 2)+1;
        int randomX = C.x + randomXOffset;
        int randomY = C.y + randomYOffset;
        if (willInteract) {
            switch (act) {
            case Action::Click:
                click(randomX, randomY);
                break;
            case Action::Swipe:
                swipe(randomX, randomY, coord.x, coord.y, 500);
                break;
            }
        }
        if (delayMilliseconds == DEFAULTDELAY) {
            wait(waitfound);
        }
        else wait(delayMilliseconds);
    }
    else {
        rebootCount++;
        if (delayMilliseconds == DEFAULTDELAY) {
            wait(waitnotfound);
        }
        else wait(delayMilliseconds);
    }
    return found;
}

bool game::fcOneTemplateA(const std::vector<std::string>& allTempl, std::string& foundTempl,Zone Z, unsigned int delayMilliseconds)
{
    return fOneTemplateA(allTempl, foundTempl,Z, delayMilliseconds, true);
}
bool game::fcOneTemplateA(const std::vector<std::string>& toclick, const std::vector<std::string>& tonotclick, std::string& foundTempl,Zone Z, unsigned int delayMilliseconds)
{   

    if (fOneTemplateA(tonotclick, foundTempl, Z, delayMilliseconds, false))return true;
    if (fcOneTemplateA(toclick, foundTempl, Z, delayMilliseconds))return true;
    return false;
}
bool game::fcOneTemplateA(const std::vector<std::string>& toclick, const std::vector<std::string> &tonotclick, Zone Z, unsigned int delayMilliseconds)
{
    bool foundclick = false;
    bool foundnoclick = false;

    foundclick = fcOneTemplateA(toclick, Z, delayMilliseconds);
    foundnoclick = fOneTemplateA(tonotclick, Z, delayMilliseconds, false);
    return foundclick || foundnoclick;
}


bool game::fOneTemplateA(std::vector<std::string> allTempl, std::string& foundTempl,Zone Z, unsigned int delayMilliseconds, bool willInteract)
{
    bool found = false;
    resetCount();
    std::vector<Template>allMats=getTemplate(allTempl);
    Template Tresult;
    loopPopUp();
    if (op.cvmtfOneTemplate(allMats, background, Tresult,Z)) {
        found = true;
        foundTempl = Tresult.id;
    }
    return templateFound(found, Tresult, willInteract, delayMilliseconds);
}

bool game::fMultipleTemplateA(const std::vector<std::string> allTempl, std::vector<std::string>& foundTemplates, Zone Z, unsigned int delayMilliseconds, bool willInteract)
{
    bool found = false;
    resetCount();
    std::vector<Template>allMats = getTemplate(allTempl);
    std::vector<Template> Tresults;
    loopPopUp();
    if (op.cvmtfMultipleTemplate(allMats, background, Tresults, Z)) {
        found = true;
        for (Template t : Tresults) {
            foundTemplates.push_back(t.id);
        }
        auto last = std::unique(foundTemplates.begin(), foundTemplates.end());
        foundTemplates.erase(last, foundTemplates.end());
    }
    return templateFound(found, Template(), willInteract, delayMilliseconds);
}

bool game::fMultipleCompareTemplateA(const std::vector<std::string> alltempl, const std::vector<std::string> simTempl, std::vector<std::string>& foundTemplates, Zone Z, unsigned int delayMilliseconds, bool willInteract)
{
    bool found = false;
    resetCount();
    std::vector<Template>allMats = getTemplate(alltempl,Color);
    std::vector<Template>allSim = getTemplate(simTempl,Color);
    std::vector<Template> Tresults;
    loopPopUp(Color);
    if (op.cvmtfMultipleTemplateCompareMultipleTemplate(allMats, background, allSim, Tresults, Z)) {
        found = true;
        for (Template t : Tresults) {
            foundTemplates.push_back(t.id);
        }
        auto last = std::unique(foundTemplates.begin(), foundTemplates.end());
        foundTemplates.erase(last, foundTemplates.end());
    }
    return templateFound(found, Template(), willInteract, delayMilliseconds);
}


bool game::fCompareOneTemplateA(const std::vector<std::string>& allTempl,const std::vector<std::string>& simTempl, std::string& foundTempl,Zone Z, unsigned int delayMilliseconds, bool willInteract)
{
    bool found = false;
    resetCount();
    std::vector<Template>allMats=getTemplate(allTempl,Color);
    std::vector<Template>simMats=getTemplate(simTempl,Color);
    Template Tresult;
    loopPopUp(Color);
    if (op.cvmtfCompareOneTemplate(allMats, background, simMats, Tresult,Z)) {
        found = true;
        foundTempl = Tresult.id;
    }
    return templateFound(found, Tresult, willInteract, delayMilliseconds);
}



bool game::fcOneTemplateA(const std::vector<std::string>& allTempl,Zone Z, unsigned int delayMilliseconds)
{
    return fOneTemplateA(allTempl,Z, delayMilliseconds, true);
}


bool game::fOneTemplateA(const std::vector<std::string>& allTempl,Zone Z, unsigned int delayMilliseconds, bool willInteract)
{
    bool found = false;
    resetCount();
    std::vector<Template>allMats=getTemplate(allTempl);
    Template Tresult;
    loopPopUp();
    if (op.cvmtfOneTemplate(allMats, background, Tresult,Z))found = true;
    return templateFound(found, Tresult, willInteract, delayMilliseconds);
}

bool game::fOneTemplateEraseA(std::vector<std::string>& allTempl, Zone Z, unsigned int delayMilliseconds, bool willInteract)
{
    bool found = false;
    resetCount();
    std::vector<Template>allMats = getTemplate(allTempl);
    Template Tresult;
    loopPopUp();
    if (op.cvmtfOneTemplate(allMats, background, Tresult, Z)) {
        eraseString(allTempl, Tresult.id);
        found = true;
    }
    return templateFound(found, Tresult, willInteract, delayMilliseconds);
}

bool game::fcOneTemplateEraseA(std::vector<std::string>& allTempl, Zone Z, unsigned int delayMilliseconds)
{
   return fOneTemplateEraseA(allTempl, Z, delayMilliseconds, true);
}


bool game::fOneMultipleTemplateA(std::vector<std::vector<std::string>> allTempl,Zone Z, unsigned int delayMilliseconds, bool willInteract)
{
    bool found = false;
    resetCount();
    std::vector<std::vector<Template>>allMats;
    std::vector<Template>Tresult;
    for (std::vector<std::string> oneAll: allTempl) {
        allMats.push_back(getTemplate(oneAll));
    }
    loopPopUp();
    if (op.cvmtfOneMultipleTemplate(allMats, background, Tresult,Z))found = true;
    return templateFound(found, Template(), willInteract, delayMilliseconds);
}



bool game::fSwipeA(std::string templ, Coords Cresult,Zone Z, bool willInteract)
{
    bool found = false;
    resetCount();
    Template Mat = getTemplate(templ);
    Template Tresult;
    loopPopUp();
    if (op.cvmtfTemplate(Mat, background, Tresult,Z))found = true;
    return templateFound(found, Tresult, willInteract, Swipe, Cresult);
}

bool game::fSwipeA(std::string templ, poswipe endx, poswipe endy,Zone Z, bool willInteract)
{
    bool found = false;
    resetCount();
    Coords Cend;
    Template Mat = getTemplate(templ);
    Template Tresult;
    loopPopUp();
    if (op.cvmtfTemplate(Mat, background, Tresult,Z)) {
        found = true;
        switch (endx) {
        case samex:
            Cend.x = C.x;
            break;
        case rightx:
            Cend.x = dimX;
            break;
        case leftx:
            Cend.x = 0;
            break;
        default:
            Cend.x = 0;
            break;
        }
        switch (endy) {
        case samey:
            Cend.y = C.y;
            break;
        case upy:
            Cend.y = 0;
            break;
        case downy:
            Cend.y = dimY;
            break;
        default:
            Cend.y = 0;
            break;
        }
    }
    return templateFound(found, Tresult, willInteract, Swipe, Cend);
}

bool game::fMultipleDigitsA(int nb, std::vector<std::string>digits, std::vector<Template>& Tresult, Zone Z) {
    std::string imagetofind;
    if (nb < digits.size()) {
        imagetofind = digits.at(nb);
    }
    Template Tdigit = getTemplate(imagetofind);
    Template Tbackg(backg, Color);
    std::vector<Template>Tdigits=getTemplate(digits);
    return op.cvmtfMultipleTemplateCompareMultipleTemplate(Tdigit, Tbackg, Tdigits, Tresult, Z);
}

Number game::fNumberIntegerA(std::vector<std::string>digits, std::vector<Unit>Units, Zone Z) {
    adb.screenshot();
    Number Ntemp;
    Digit Dtemp;
    std::vector<Template> Tresult;
    for (int i = 0; i < digits.size(); ++i) {
        if (fMultipleDigitsA(i, digits, Tresult, Z)) {
            for (Template Templ : Tresult){
                Dtemp.Cnb = Templ.C;
                Dtemp.dig = i;
                Ntemp.digits.push_back(Dtemp);
            }
        }
    }
    std::vector<std::string>allsameImages;
    for (std::string image : digits) {
        allsameImages.push_back(image);
    }
    for (Unit image : Units) {
        allsameImages.push_back(image.nameunit);
    }
    orderDigits(Ntemp.digits);
    for (int l = 0; l < Ntemp.digits.size(); ++l) {
        Ntemp.nb += Ntemp.digits.at(l).dig * pow(10, Ntemp.digits.size() - l - 1);
    }
    std::cout << Ntemp.nb << std::endl;
    for (Unit u : Units) {
        switch (u.Ord) {

        case Orders::noOrd:
            break;
        case Orders::K:
            if (fCompareMultipleTemplateA(u.nameunit, allsameImages, Z)) {
                Ntemp.K = true;
                Ntemp.nb *= pow(10, 3);
                std::cout << Ntemp.nb << std::endl;
                return Ntemp;
            }
            break;
        case Orders::M:
            if (fCompareMultipleTemplateA(u.nameunit, allsameImages, Z)) {
                Ntemp.M = true;
                Ntemp.nb *= pow(10, 6);
                std::cout << Ntemp.nb << std::endl;
                return Ntemp;
            }
            break;
        case Orders::B:
            if (fCompareMultipleTemplateA(u.nameunit, allsameImages, Z)) {
                Ntemp.B = true;
                Ntemp.nb *= pow(10, 9);
                std::cout << Ntemp.nb << std::endl;
                return Ntemp;
            }
            break;
        case Orders::T:
            if (fCompareMultipleTemplateA(u.nameunit, allsameImages, Z)) {
                Ntemp.T = true;
                Ntemp.nb *= pow(10, 12);
                std::cout << Ntemp.nb << std::endl;
                return Ntemp;
            }
            break;
        }

    }
    std::cout << Ntemp.nb << std::endl;
    return Ntemp;
}

Number game::fNumberIntegerA(std::vector<std::string>digits, Zone Z) {
    adb.screenshot();
    Number Ntemp;
    Digit Dtemp;
    std::vector<Template> Tresult;
    for (int i = 0; i < digits.size(); ++i) {
        if (fMultipleDigitsA(i, digits, Tresult, Z)) {
            for (Template Templ : Tresult) {
                Dtemp.Cnb = Templ.C;
                Dtemp.dig = i;
                Ntemp.digits.push_back(Dtemp);
            }
        }
    }
    std::vector<std::string>allsameImages;
    for (std::string image : digits) {
        allsameImages.push_back(image);
    }
    orderDigits(Ntemp.digits);
    for (int l = 0; l < Ntemp.digits.size(); ++l) {
        Ntemp.nb += Ntemp.digits.at(l).dig * pow(10, Ntemp.digits.size() - l - 1);
    }
    std::cout << Ntemp.nb << std::endl;
    return Ntemp;
}

Number game::fNumberDecimalA(std::vector<std::string>digits, std::vector<Unit>Units, std::string dot, Zone Z) {
    adb.screenshot();
    Number Ntemp;
    Digit Dtemp;
    std::vector<Template> Tresult;
    for (int i = 0; i < digits.size(); ++i) {
        if (fMultipleDigitsA(i, digits, Tresult, Z)) {
            for (Template Templ : Tresult) {
                Dtemp.Cnb = Templ.C;
                Dtemp.dig = i;
                Ntemp.digits.push_back(Dtemp);
            }
        }
    }

    std::vector<std::string>allsameImages;
    for (std::string image : digits) {
        allsameImages.push_back(image);
    }
    for (Unit image : Units) {
        allsameImages.push_back(image.nameunit);
    }
    Coords Cdot;
    if (fCompareMultipleTemplateA(dot, allsameImages, Z)) {
        Ntemp.decimal = true;
        Cdot = C;
        std::cout << "DECIMAL NUMBER" << std::endl;
    }
    orderDigits(Ntemp.digits);
    for (int l = 0; l < Ntemp.digits.size(); ++l) {
        Ntemp.nb += Ntemp.digits.at(l).dig * pow(10, Ntemp.digits.size() - l - 1);
    }
    std::cout << Ntemp.nb << "\n";
    if (Ntemp.decimal == true) {
        for (int i = 0; i < Ntemp.digits.size(); i++) {
            if (Cdot.x < Ntemp.digits.at(i).Cnb.x) {
                Ntemp.dotposition = i;
                Ntemp.nb /= pow(10, Ntemp.digits.size() - i);
                std::cout << "Dot position:" << i << std::endl;
                break;
            }
        }
    }
    std::cout << Ntemp.nb << std::endl;
    for (Unit u : Units) {
        switch (u.Ord) {

        case Orders::noOrd:

            break;
        case Orders::K:
            if (fCompareMultipleTemplateA(u.nameunit, allsameImages, Z)) {
                Ntemp.K = true;
                Ntemp.nb *= pow(10, 3);
                std::cout << Ntemp.nb << std::endl;
                return Ntemp;
            }
            break;
        case Orders::M:
            if (fCompareMultipleTemplateA(u.nameunit, allsameImages, Z)) {
                Ntemp.M = true;
                Ntemp.nb *= pow(10, 6);
                std::cout << Ntemp.nb << std::endl;
                return Ntemp;
            }
            break;
        case Orders::B:
            if (fCompareMultipleTemplateA(u.nameunit, allsameImages, Z)) {
                Ntemp.B = true;
                Ntemp.nb *= pow(10, 9);
                std::cout << Ntemp.nb << std::endl;
                return Ntemp;
            }
            break;
        case Orders::T:
            if (fCompareMultipleTemplateA(u.nameunit, allsameImages, Z)) {
                Ntemp.T = true;
                Ntemp.nb *= pow(10, 12);
                std::cout << Ntemp.nb << std::endl;
                return Ntemp;
            }
            break;
        }
    }
    std::cout << Ntemp.nb << std::endl;
    return Ntemp;
}

Number game::fNumberDecimalA(std::vector<std::string>digits, std::string dot, Zone Z) {
    adb.screenshot();
    Number Ntemp;
    Digit Dtemp;
    std::vector<Template> Tresult;
    for (int i = 0; i < digits.size(); ++i) {
        if (fMultipleDigitsA(i, digits, Tresult, Z)) {
            for (Template Templ : Tresult) {
                Dtemp.Cnb = Templ.C;
                Dtemp.dig = i;
                Ntemp.digits.push_back(Dtemp);
            }
        }
    }

    std::vector<std::string>allsameImages;
    for (std::string image : digits) {
        allsameImages.push_back(image);
    }
    Coords Cdot;
    if (fCompareMultipleTemplateA(dot, allsameImages, Z)) {
        Ntemp.decimal = true;
        Cdot = C;
        std::cout << "DECIMAL NUMBER" << std::endl;
    }
    orderDigits(Ntemp.digits);
    for (int l = 0; l < Ntemp.digits.size(); ++l) {
        Ntemp.nb += Ntemp.digits.at(l).dig * pow(10, Ntemp.digits.size() - l - 1);
    }
    std::cout << Ntemp.nb << std::endl;
    if (Ntemp.decimal == true) {
        for (int i = 0; i < Ntemp.digits.size(); i++) {
            if (Cdot.x < Ntemp.digits.at(i).Cnb.x) {
                Ntemp.dotposition = i;
                Ntemp.nb /= pow(10, Ntemp.digits.size() - i);
                std::cout << "Dot position:" << i << std::endl;
                break;
            }
        }
    }
    std::cout << Ntemp.nb << std::endl;
    return Ntemp;
}












