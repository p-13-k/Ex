#include <iostream>
#include <string>
#include <vector>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
using namespace std;
using namespace cpr;
using json = nlohmann::json;
const string API_KEY = "bad88bca35a3f14cca1ff55ee0919340"; 
vector<string> favorites; 
void displayWeather(const string& cityName) {
    Response r = cpr::Get(Url{"https://api.openweathermap.org/data/2.5/weather"},
                          Parameters{{"q", cityName}, {"appid", API_KEY}, {"units", "metric"}});
    if (r.status_code != 200) {
        cout << "Error fetching weather for " << cityName << ". Please try again.\n";
        return;
    }
    json data = json::parse(r.text);
    cout << "Weather in " << data["name"] << ", " << data["sys"]["country"] << ":\n";
    cout << "Temperature: " << data["main"]["temp"] << "°C\n";
    cout << "Description: " << data["weather"][0]["description"] << "\n\n";
}
void addFavorite(const string& cityName) {
    if (favorites.size() >= 3) {
        cout << "Favorites list is full. Please remove a city first.\n";
        return;
    }
    favorites.push_back(cityName);
    cout << cityName << " added to favorites.\n";
}
void removeFavorite(const string& cityName) {
    auto it = find(favorites.begin(), favorites.end(), cityName);
    if (it != favorites.end()) {
        favorites.erase(it);
        cout << cityName << " removed from favorites.\n";
    } else {
        cout << cityName << " is not in the favorites list.\n";
    }
}
void displayFavorites() {
    if (favorites.empty()) {
        cout << "No favorite cities added yet.\n";
        return;
    }
    for (const string& city : favorites) {
        cout << "Fetching weather for " << city << "...\n";
        displayWeather(city);
    }
}
int main() {
    int choice;
    string cityName;
    while (true) {
        cout << "1. Search for a city\n";
        cout << "2. Add to favorites\n";
        cout << "3. List favorites\n";
        cout << "4. Remove from favorites\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter city name: ";
                cin >> cityName;
                displayWeather(cityName);
                break;
            case 2:
                cout << "Enter city name to add to favorites: ";
                cin >> cityName;
                addFavorite(cityName);
                break;
            case 3:
                displayFavorites();
                break;
            case 4:
                cout << "Enter city name to remove from favorites: ";
                cin >> cityName;
                removeFavorite(cityName);
                break;
            case 5:
                cout << "Exiting program. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
