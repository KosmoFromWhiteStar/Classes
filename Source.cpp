#include <iostream>
#include <ctime>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>

#pragma warning(disable: 4996)

bool compare(std::string inP_word, std::string command)
{
	for (int i = 0; i < inP_word.length() && i < command.length(); i++)
	{
		if (inP_word[i] != command[i])
		{
			return false;
		}
	}
	return true;
}

struct Track
{
	std::string name = "";
	std::string artist = "";
	std::time_t time = std::time(nullptr);
	std::tm create_date = *std::localtime(&time);
	int duration_sec = 0;

	void name_song()
	{
		std::cout << "Input name song: " << std::endl;
		(std::cin >> name).get();
	}
};

class Player
{
private:
	std::vector <Track> list_track;
	bool swithcer = true;                   // turn off / turn on 
	bool status_play = false;               // false player on pause
	unsigned int now_play = 0;              //index of track plaied now

	void track_display ()
	{ 
		if (list_track.capacity() == 0 || now_play > list_track.capacity())
		{
			std::cerr << "Invalid track" << std::endl;
			return;
		}
		std::cout << "Played: " << list_track[now_play].name << std::endl;
		std::cout << "Artist: " << list_track[now_play].artist << std::endl;
		std::cout << "Duration: " << list_track[now_play].duration_sec << std::endl;
	}
	void read_song     ()
	{
		std::ifstream music("music\\list.bin", std::ios::binary);
		if (!music.is_open())
		{
			std::cout << "File doesn't open" << std::endl;
			return;
		}

		Track song;
		while (music.eof())
		{
			int len = 0;
			music.read((char*)(&len), sizeof(len));
			music.read((char*)&(song.name), len);
			music.read((char*)(&len), sizeof(len));
			music.read((char*)&(song.artist), len);
			music.read((char*)&(song.duration_sec), sizeof(song.duration_sec));
			music.read((char*)&(song.time), sizeof(song.time));
			song.create_date = *std::localtime(&(song.time));
			list_track.push_back(song);
		}
		music.close();
	}

public:

	void write_song ()
	{
		Track song;
		std::ofstream music("music\\list.bin", std::ios::binary & std::ios::app);
		if (!music.is_open())
		{
			std::cout << "File doesn't open" << std::endl;
			return;
		}
		
		song.name_song();
		int len = song.name.length();
		music.write((char*)(&len), sizeof(len));
		music.write((char*)&(song.name), len);

		std::cout << "Input artist song: " << std::endl;
		std::getline(std::cin, song.artist);

		len = song.artist.length();
		music.write((char*)(&len), sizeof(len));
		music.write((char*)&(song.artist), len);

		std::cout << "Input sign duration (sec): " << std::endl;
		std::cin >> song.duration_sec;
		music.write((char*)&(song.duration_sec), sizeof(song.duration_sec));

		std::cout << "Input create date: " << std::endl << "Use format  DD.MM.YYYY" << std::endl;
		std::cin >> std::get_time(&(song.create_date), "%d.%m.%Y");
		song.time = std::mktime(&(song.create_date));
		music.write((char*)&(song.time), sizeof(song.time));

		list_track.push_back(song);
		music.close();
	}
	void play       ()
	{
		if (list_track.size() == 0) read_song();
		if (status_play) return;
		status_play = true;
		track_display();
	}
	void pause      ()
	{
		if (!status_play) return;

		std::cout << "track pasued" << std::endl;
		status_play = false;
		system("Pause");
	}
	void next       ()
	{
		now_play = std::rand() % list_track.size();
		track_display();
	}
	void list       ()
	{
		for (int i = 0; i < list_track.size(); i++)
		{
			std::cout << "------------------" << std::endl;
			now_play = i;
			track_display();
		}
	}
	void exit       ()
	{
		swithcer = false;
	}
	bool status     () { return swithcer; }
};

int main()
{
	Player mp3player;
	std::string command = "";
	
	do
	{
		std::cout << "Input command: " << std::endl;
		std::cin >> command;
		if (compare(command, "write")) mp3player.write_song();
		if (compare(command, "play")) mp3player.play();
		if (compare(command, "pause")) mp3player.pause();
		if (compare(command, "next")) mp3player.next();
		if (compare(command, "list")) mp3player.list();
		if (compare(command, "exit")) mp3player.exit();
	
	} while (mp3player.status());
	return 0;
}
