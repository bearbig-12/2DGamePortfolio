#include "Score_Sub.h"

int Score_Sub::Player_Score;
std::vector<int> Score_Sub::scores;


Score_Sub::~Score_Sub()
{
	if (Player_Score >= 99)
	{
		std::cout << "[Score] Total Player  Score [" << 99 << "] !!!!\n";

	}
	else
	{
		std::cout << "[Score] Total Player  Score [" << Player_Score << "] !!!!\n";

	}
	WriteHTML(html_path);
}

void Score_Sub::InitScore(std::string file_path)
{
	Player_Score = 0;
	html_path = file_path;
	ReadHTML(html_path);
}

void Score_Sub::UpdateSubsystem()
{
	HandleEvents();
}



void Score_Sub::ReadHTML(std::string file_path)
{
	std::cout << "[Score] Score read\n";

	std::ifstream html_in;
	bool inside = false; // To check score value 
	bool scoreDone = true; // To check if the score is double digit number 
	int line = 0;

	html_in.open(file_path, std::ios::in);
	if (html_in.fail()) {
		std::cout << "\n[Score] Error file (" << file_path << ") not found!\nCheck directory path and typos\n";
	}
	else {
		while (std::getline(html_in, score_data)) {
			//std::cout << score_data  << '\n';
			for (char c : score_data) {
				if (c == ')') {
					inside = true;
					scoreDone = false;
				}
				if (c == 's') {
					inside = false;
				}
				if (c == '!')
				{
					scoreDone = true;
					inside = false;
				}
				if (inside) {
					if (c != ')' && c != ' ') 
					{
						temp.push_back((int)c - '0'); // Need to convert char to int. 
						// Subtracting '0' (which is 48) from the decimal gets us the number behind the character (e.g. 53 - 48 is 5)
						//std::cout << c << '\n';
					}
				}
				// Sometime, can get double-digit numer as a score. 
				// For this case, added a scoreDone boolean type to figuer out double digit.
				if (scoreDone)
				{
					if (temp.size() == 1)
					{
						scores.push_back(temp[0]);
						
						temp.clear();
						scoreDone = false;
					}
					if (temp.size() == 2)
					{
						int a = temp[0] * 10;
						int b = temp[1];
						int c = a + b;
						scores.push_back(c);

						temp.clear();
						scoreDone = false;
					}
					
				}
				
			}
		}
	}
	html_in.close();

	std::sort(scores.begin(), scores.end(), std::greater<int>());
	for (int i = 0; i < scores.size(); ++i) {
		std::cout << scores[i] << '\n';
	}
}

void Score_Sub::WriteHTML(std::string file_path)
{

	std::cout << "[Score] Score written\n";

	int line = 0;
	std::ifstream html_in;
	html_in.open(file_path, std::ios::in);
	//Before writh html use sort function to make a descending order
	scores.push_back(Player_Score);
	std::sort(scores.begin(), scores.end(), std::greater<int>());
	if (scores[0] >= 99)
	{
		scores[0] = 99;
	}
	while (std::getline(html_in, score_data)) {
		//std::cout << score_data << '\n';
		// Do not need to check the score because of sort function.
		// It already sorted(descedning) the scores in order.
		// So, just need to overwrite it.
		if (line == 5) 
		{
			overwrite_score_data = ("<p> 1) ");
			overwrite_score_data += std::to_string(scores[0]);
			overwrite_score_data += "! scores </p>";
			overwrite_scores_list.push_back(overwrite_score_data);
		}
		else if (line == 6) 
		{
			overwrite_score_data = ("<p> 2) ");
			overwrite_score_data += std::to_string(scores[1]);
			overwrite_score_data += "! scores </p>";
			overwrite_scores_list.push_back(overwrite_score_data);
		}
		else if (line == 7) 
		{
			overwrite_score_data = ("<p> 3) ");
	
			overwrite_score_data += std::to_string(scores[2]);

			overwrite_score_data += "! scores </p>";
			overwrite_scores_list.push_back(overwrite_score_data);
		}
		else if (line == 8) 
		{
			overwrite_score_data = ("<p> 4) ");
			overwrite_score_data += std::to_string(scores[3]);

			overwrite_score_data += "! scores </p>";
			overwrite_scores_list.push_back(overwrite_score_data);
		}
		else if (line == 9)
		{
			overwrite_score_data = ("<p> 5) ");
			overwrite_score_data += std::to_string(scores[4]);

			overwrite_score_data += "! scores </p>";
			overwrite_scores_list.push_back(overwrite_score_data);
		}
		else
		{
			overwrite_scores_list.push_back(score_data);
		}

		++line;
	}
	html_in.close();

	std::ofstream html_out;
	html_out.open(file_path, std::ios::out);
	for (int i = 0; i < overwrite_scores_list.size(); ++i) {
		html_out << overwrite_scores_list[i];
		html_out << '\n';
	}
	for (int i = 0; i < scores.size() - 1; i++)
	{
		std::cout << " High Scores  " << i + 1 << " : " << scores[i] << std::endl;

	}
	html_out.close();
}

void Score_Sub::HandleEvents()
{
	for (Event* event : EventHandler::GetEvents()) {
		switch (event->GetEventType())
		{
		case EventType::LoadLevel:
			Player_Score = 0;
			break;

		case EventType::EnemyDestoryed:
			Player_Score++;
			break;
		case EventType::getDamage:
			Player::Player_Hp--;
			break;
		}
		

	}
}
