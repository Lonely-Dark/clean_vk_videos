#include <iostream>
#include "json/single_include/nlohmann/json.hpp"
#include <cpr/cpr.h>
#include <string>
#include <thread>
#include <chrono> 

using json = nlohmann::json;
using namespace std;

string GetVk(string &token)
{
	cpr::Response res = cpr::Get(cpr::Url{"https://api.vk.com/method/video.get"}, cpr::Parameters{{"access_token", token}, {"v", "5.102"}, {"owner_id", "186752691"}, {"count", "200"}});
	
	return res.text;
}

void DeleteVideo(json::iterator &iter, string token)
{
	int count = 0;

	cpr::Response res = cpr::Get(cpr::Url{"https://api.vk.com/method/video.delete"}, cpr::Parameters{{"access_token", token}, {"owner_id", to_string((*iter)["owner_id"])}, {"video_id", to_string((*iter)["id"])}, {"target_id", "186752691"}, {"v", "5.102"}});
	
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
	string token_m = argv[1];
	auto vk_response = json::parse(GetVk(token_m).c_str());
	auto videos = vk_response["response"]["items"];
	int countVideos = vk_response["response"]["count"];

	cout << "ALL: " << to_string(countVideos) << endl;
	cout << "Deleting..." << endl;

	for (json::iterator it = videos.begin(); it != videos.end(); ++it)
	{
		DeleteVideo(it, token_m);
	}

	return 0;
}
