#pragma once
#include "SubSystem_Manager.h"
#include <fstream>
#include <algorithm>
#include <string>
#include "Event.h"
#include "EventHandler.h"
#include "Player.h"
class Score_Sub 
{
public:
    ~Score_Sub();

    void InitScore(std::string file_path);
    void UpdateSubsystem();
    static int GetCurrentScore() { return Player_Score; }
    static int GetHighestScore() { return scores[0]; }
    // Read the scores from Highscore html file.
    void ReadHTML(std::string file_path);
    // Write and Overwrite the scores to Highscore html file after the game.
    void WriteHTML(std::string file_path);
    static int Player_Score;
private:
    void HandleEvents();

  

    // Highscore variables
    std::string score_data; // The score data which come from our highscore html file.
    static std::vector<int> scores; // the high score values, 
    std::vector<int> temp; // We need to also read double digit int number. For this, we need temp container to store 2 int.
    std::string overwrite_score_data; // After the game play, we need to over write the scores in HTML file.
    std::vector<std::string> overwrite_scores_list; // Stores the edited highscore and Put it in to HTML file as a string.

    std::string html_path; // The file path for html
};

