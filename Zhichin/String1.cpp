#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct song {
	string artist;
	string title;
};

bool UniquenessCheck(const vector<string>& artists, const string& artist) {  //проверка уникальных исполнителей
	for (auto& x : artists) {
		if (x == artist)
			return true;
	}
	return false;
}

int SongCount(const vector<song>& songs, const string& artist) {  //подсчёт песен определённого исполнителя
	int cnt = 0;
	for (auto& x : songs) {
		if (x.artist == artist)
			cnt++;
	}
	return cnt;
}

int main() {
	vector<song> list;
	int n;

	cout << "How many songs do you want to add: ";
	cin >> n;
	cin.ignore();

	for (int i = 0; i < n; i++) {
		song song1;
		string str;

		cout << "Enter artist and song title: ";
		getline(cin, str);

		size_t space = str.find(' ');

		if (space != string::npos) {
			song1.artist = str.substr(0, space);
			song1.title = str.substr(space + 1);
			list.push_back(song1);
		}
		else {
			cout << "Error: no data" << endl;
			i--;
		}
	}
	vector<string> UniqueArtist;  //список уникальный исполнителей

	for (auto& song : list) {
		if (!UniquenessCheck(UniqueArtist, song.artist))
			UniqueArtist.push_back(song.artist);
	}

	cout << endl;
	cout << "Number of songs: " << list.size() << endl;
	cout << "Artist and his songs: " << endl;

	for (auto& artist : UniqueArtist) {
		int cnt = SongCount(list, artist);

		cout << artist << ": " << cnt << " songs" << endl;
	}
	return 0;
}
