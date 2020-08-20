#include <iostream>
#include "json/single_include/nlohmann/json.hpp"
#include <cpr/cpr.h>
#include <string>
#include <thread>
#include <chrono> 

using json = nlohmann::json;
using namespace std;

string GetVk(string &token, string &page_id)
{
	cpr::Response res = cpr::Get(cpr::Url{"https://api.vk.com/method/video.get"}, cpr::Parameters{{"access_token", token}, {"v", "5.102"}, {"owner_id", page_id}, {"count", "200"}});
	
	return res.text;
}

void DeleteVideo(json::iterator &iter, string &token, string &page_id)
{
	int count = 0;

	cpr::Response res = cpr::Get(cpr::Url{"https://api.vk.com/method/video.delete"}, cpr::Parameters{{"access_token", token}, {"owner_id", to_string((*iter)["owner_id"])}, {"video_id", to_string((*iter)["id"])}, {"target_id", page_id}, {"v", "5.102"}});
	
	auto end = json::parse(res.text);

	if (end["response"] == 1)
	{
		count+=1;
		cout << "Deleted: " << count << endl;
	}
	else
	{
		cout << "Something wrong" << endl;
	}

	this_thread::sleep_for(chrono::seconds(3));
}

int main(int argc, char* argv[])
{
	if (argv[1] && argv[2])
	{
		cout << "Hello! Working...\n";
		cout << "Videos in profile delete V1.0\n\n";
	}
	else
	{
		cout << "Two arguments are not specified: VK token or page id\n";
		return 0;
	}
	string token_m = argv[1];
	string id_page = argv[2];
	auto vk_response = json::parse(GetVk(token_m, id_page).c_str());
	auto videos = vk_response["response"]["items"];
	int countVideos = vk_response["response"]["count"];

	cout << "ALL: " << to_string(countVideos) << endl;
	cout << "Deleting..." << endl;

	for (json::iterator it = videos.begin(); it != videos.end(); ++it)
	{
		DeleteVideo(it, token_m, id_page);
	}

	return 0;
}
