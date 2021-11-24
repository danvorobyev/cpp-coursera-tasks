#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <cstdint>
#include <queue>

using namespace std;

struct BookEvent {
    int client_id;
    int room_count;
    int64_t time;
};

class HotelManager {
public:
    void Book(int64_t time, int client_id, int room_count) {
        events_.push({client_id, room_count, time});
        room_count_ += room_count;
        ++client_bookings_[client_id];
    }

    int Clients(int64_t time) {
        TimeAdjust(time);
        return client_bookings_.size();
    }

    int Rooms(int64_t time) {
        TimeAdjust(time);
        return room_count_;
    }

private:
    int room_count_ = 0;
    map<int, int> client_bookings_;
    queue<BookEvent> events_;

    void TimeAdjust(int64_t time) {
        while (!events_.empty() 
            && events_.front().time <= time - 86400) {
            const auto& event = events_.front();
            room_count_ -= event.room_count;
            if (--client_bookings_[event.client_id] == 0)
                client_bookings_.erase(event.client_id);
            events_.pop();
        }
    }
};

class BookingManager {
public:
    void Book(int64_t time, const string& hotel_name,
             int client_id, int room_count) {
        current_time_ = time;
        hotels_[hotel_name].Book(time, client_id, room_count);        
    }

    int Clients(const string& hotel_name) {
        if (hotels_.find(hotel_name) == hotels_.end())
            return 0;
        return hotels_.at(hotel_name).Clients(current_time_);
    }

    int Rooms(const string& hotel_name) {
        if (hotels_.find(hotel_name) == hotels_.end())
            return 0;
        return hotels_.at(hotel_name).Rooms(current_time_);
    }
private:
    int64_t current_time_;
    map<string, HotelManager> hotels_;
};




int main() {
    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    BookingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        string hotel_name;

        if (query_type == "BOOK") {
            int64_t time;
            int client_id, room_count;
            cin >> time >> hotel_name >> client_id >> room_count;
            manager.Book(time, hotel_name, client_id, room_count);
        } else if (query_type == "CLIENTS") {
            cin >> hotel_name;
            cout << manager.Clients(hotel_name) << '\n';
        } else if (query_type == "ROOMS") {
            cin >> hotel_name;
            cout << manager.Rooms(hotel_name) << '\n';
        }
    }
    return 0;
}