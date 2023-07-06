
#include <bits/stdc++.h>
using namespace std;
ofstream out_file("dust_sdddensor.csv");
ofstream log_file("log.txt");
struct DateTime
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    void printDatetime()
    {
        out_file << setfill('0');
        out_file << setw(4) << this->year << ":" << setw(2) << this->month << ":" << setw(2) << this->day << " "
                 << setw(2) << this->hour << ":" << setw(2) << this->minute << ":" << setw(2) << this->second;
    }
    void print()
    {
        cout << setfill('0');
        cout << setw(4) << this->year << ":" << setw(2) << this->month << ":" << setw(2) << this->day << " "
             << setw(2) << this->hour << ":" << setw(2) << this->minute << ":" << setw(2) << this->second;
    }
    void write_to_file(string filepath)
    {
        ofstream write_file(filepath);
        write_file << setfill('0');
        write_file << setw(4) << this->year << ":" << setw(2) << this->month << ":" << setw(2) << this->day << " "
                   << setw(2) << this->hour << ":" << setw(2) << this->minute << ":" << setw(2) << this->second << endl;
    }
};

bool compare(DateTime time1, DateTime time2)
{
    if (time1.year < time2.year)
    {
        return true;
    }
    else if (time1.year > time2.year)
    {
        return false;
    }

    if (time1.month < time2.month)
    {
        return true;
    }
    else if (time1.month > time2.month)
    {
        return false;
    }

    if (time1.day < time2.day)
    {
        return true;
    }
    else if (time1.day > time2.day)
    {
        return false;
    }

    if (time1.hour < time2.hour)
    {
        return true;
    }
    else if (time1.hour > time2.hour)
    {
        return false;
    }

    if (time1.minute < time2.minute)
    {
        return true;
    }
    else if (time1.minute > time2.minute)
    {
        return false;
    }

    if (time1.second < time2.second)
    {
        return true;
    }

    else
    {
        return false;
    }
}

bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int getDaysInMonth(int month, int year)
{
    if (month == 2)
    {
        if (isLeapYear(year))
        {
            return 29;
        }
        else
        {
            return 28;
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        return 30;
    }
    else
    {
        return 31;
    }
}

DateTime addSeconds(const DateTime &dateTime, int seconds)
{
    DateTime result = dateTime;
    result.second += seconds;

    // Xử lý tràn giây
    if (result.second >= 60)
    {
        int extraMinutes = result.second / 60;
        result.second %= 60;
        result.minute += extraMinutes;

        // Xử lý tràn phút
        if (result.minute >= 60)
        {
            int extraHours = result.minute / 60;
            result.minute %= 60;
            result.hour += extraHours;

            // Xử lý tràn giờ
            if (result.hour >= 24)
            {
                int extraDays = result.hour / 24;
                result.hour %= 24;
                result.day += extraDays;

                // Xử lý tràn ngày
                while (true)
                {
                    int daysInMonth = getDaysInMonth(result.month, result.year);

                    if (result.day > daysInMonth)
                    {
                        result.day -= daysInMonth;
                        result.month++;

                        if (result.month > 12)
                        {
                            result.month = 1;
                            result.year++;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
    }

    return result;
}

DateTime getCurrentDateTime()
{
    time_t now = time(nullptr);
    tm *timeinfo = localtime(&now);

    DateTime currentDateTime;
    currentDateTime.year = timeinfo->tm_year + 1900; // Năm tính từ 1900
    currentDateTime.month = timeinfo->tm_mon + 1;    // Tháng tính từ 0
    currentDateTime.day = timeinfo->tm_mday;
    currentDateTime.hour = timeinfo->tm_hour;
    currentDateTime.minute = timeinfo->tm_min;
    currentDateTime.second = timeinfo->tm_sec;

    return currentDateTime;
}
struct Simulation
{
    int id;
    DateTime time;
    double value;
    void printSimulation()
    {
        out_file << id << ",";
        time.printDatetime();
        out_file << "," << value << endl;
    }
};
double randomValue()
{
    return rand() % 10001 / 10.0;
}

void sol(int n, int st, int si)
{
    out_file << "id,time,value" << endl;
    DateTime start_time = getCurrentDateTime();
    // DateTime start_time;
    // start_time.day = 31;
    // start_time.month = 12;
    // start_time.year = 2023;
    // start_time.hour = 20;
    // start_time.minute = 0;
    // start_time.second = 0;
    DateTime end_time = addSeconds(start_time, si * 3600);
    while (compare(start_time, end_time))
    {
        for (int i = 1; i <= n; i++)
        {
            DateTime temp_time = start_time;
            int id = i;
            double value = randomValue();
            Simulation temp;
            temp.id = id;
            temp.time = temp_time;
            temp.value = value;
            temp.printSimulation();
        }
        start_time = addSeconds(start_time, st);
    }
}
void printError()
{
    printf("Error: invalid command");
}
double extract_value(string line)
{
    stringstream ss(line);
    string token;
    vector<double> values;

    while (getline(ss, token, ','))
    {
        double x = stof(token);
        values.push_back(x);
    }
    return values.back();
}
int extract_id(string line)
{
    size_t pos = line.find(',');
    int id = std::stoi(line.substr(0, pos));
    return id;
}
int random_task2_2(int a, int b)
{
    std::random_device rd;
    std::mt19937 generator(rd());

    std::uniform_int_distribution<int> distribution(a, b - 1);
    int randomValue = distribution(generator);
    return randomValue;
}

string task_2_2(double c)
{
    string s;

    if (c >= 0 && c < 12)
    {
        // 0<= x < 12;
        double x = (c - 0) * (50 - 0) / (12 - 0);
        int aqi = std::round(x);
        s = "," + std::to_string(aqi) + ",Good";
    }
    else if (c >= 12 && c < 35.5)
    {
        // std::cout << "Trường hợp 12 ≤ c < 35.5" << std::endl;
        // int x = random_task2_2(50, 100);
        double x = 50 + (c - 12) * (100 - 50) / (35.5 - 12);
        int aqi = std::round(x);
        s = "," + std::to_string(aqi) + ",Moderate";
    }
    else if (c >= 35.5 && c < 55.5)
    {
        // std::cout << "Trường hợp 35.5 ≤ c < 55.5" << std::endl;
        // int x = random_task2_2(100, 150);
        double x = 100 + (c - 35.5) * (150 - 100) / (55.5 - 35.5);
        int aqi = std::round(x);
        s = "," + std::to_string(aqi) + ",Slightly unhealthy";
    }
    else if (c >= 55.5 && c < 150.5)
    {
        // std::cout << "Trường hợp 55.5 ≤ c < 150.5" << std::endl;
        // int x = random_task2_2(150, 200);
        double x = 150 + (c - 55.5) * (200 - 150) / (150.5 - 55.5);
        int aqi = std::round(x);
        s = "," + std::to_string(aqi) + ",Unhealthy";
    }
    else if (c >= 150.5 && c < 250.5)
    {
        // std::cout << "Trường hợp 150.5 ≤ c < 250.5" << std::endl;
        // int x = random_task2_2(200, 300);
        double x = 200 + (c - 150.5) * (300 - 200) / (250.5 - 150.5);
        int aqi = std::round(x);
        s = "," + std::to_string(aqi) + ",Very unhealthy";
    }
    else if (c >= 250.5 && c < 350.5)
    {
        // std::cout << "Trường hợp 250.5 ≤ c < 350.5" << std::endl;
        // int x = random_task2_2(300, 400);
        double x = 300 + (c - 250.5) * (400 - 300) / (350.5 - 250.5);
        int aqi = std::round(x);
        s = "," + std::to_string(aqi) + ",Hazardous";
    }
    else
    {
        // std::cout << "Trường hợp 350.5 ≤ c ≤ 550.5" << std::endl;
        // int x = random_task2_2(400, 500);
        double x = 400 + (c - 350.5) / (550.5 - 350.5) * (500 - 400);
        int aqi = std::round(x);
        s = "," + std::to_string(aqi) + ",Extremely hazardous";
    }

    return s;
}

void filter_(string filepath)
{
    ifstream i_file(filepath);
    ofstream task2_1_file("task2_1.csv");
    ofstream task2_2_file("task2_2.csv");
    if (!i_file.is_open())
    {
        cout << "Không thể mở file!" << endl;
    }
    // đọc dòng đầu tiên
    string line_0;
    getline(i_file, line_0);
    task2_2_file << line_0 << endl;
    int count = 0;
    string rs = "";
    // đọc các dòng tiếp
    string line;
    while (getline(i_file, line))
    {
        bool check = false;

        double x = extract_value(line);

        if (x < 5 || x > 550.5)
        {
            check = true;
        }
        if (check)
        {
            rs += line + "\n";
            count++;
        }
        if (!check)
        {
            task2_2_file << line << endl;
        }
    }

    task2_1_file << "number of outliers: " << count << endl;
    task2_1_file << line_0 + "\n" + rs;
}
DateTime stringToDate(const std::string &dateTimeStr)
{
    DateTime dateTime;

    std::stringstream ss(dateTimeStr);

    char delimiter;

    ss >> dateTime.year >> delimiter >> dateTime.month >> delimiter >> dateTime.day >> dateTime.hour >> delimiter >> dateTime.minute >> delimiter >> dateTime.second;

    return dateTime;
}
string string_to_time(string line)
{
    std::istringstream ss(line);
    int id;
    std::string time;
    ss >> id;
    ss.ignore();
    std::getline(ss, time, ',');
    return time;
}
std::string dateToString(const DateTime &dateTime)
{
    std::stringstream ss;
    ss << dateTime.year << ":" << dateTime.month << ":" << dateTime.day << " " << dateTime.hour << ":" << dateTime.minute << ":" << dateTime.second;
    return ss.str();
}
std::string getLastLine(const std::string &filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Failed to open the file." << std::endl;
        return "";
    }

    std::string line;
    std::string lastLine;

    while (std::getline(file, line))
    {
        lastLine = line;
    }

    file.close();

    return lastLine;
}

DateTime getHour(const DateTime &datetime)
{
    DateTime result = datetime;
    result.minute = 0;
    result.second = 0;
    return result;
}
double roundToOneDecimal(double num)
{
    return round(num * 10) / 10;
}
void sol_average(string filepath, string file_filter, string ouput)
{
    ifstream dust_sensor(filepath);
    ofstream filter(ouput);
    ifstream filter2_2_(file_filter);
    // lấy thời gian đầu tiên trong file dust_sim sau đó tính trung bình của các id từng giờ.
    if (dust_sensor.is_open())
    {
        string line_0;
        getline(dust_sensor, line_0);
    }
    else
    {
        throw std::runtime_error("Lỗi: Không thể mở tệp tin.");
    }
    filter << "id,time,value,aqi,pollution" << endl;
    string line1;
    getline(dust_sensor, line1);
    DateTime current_time = stringToDate(string_to_time(line1));
    current_time = (getHour(current_time));
    DateTime end_time = stringToDate(string_to_time(getLastLine(filepath)));
    end_time = addSeconds(getHour(end_time), 3600 + 1);
    string line0_;
    getline(filter2_2_, line0_);
    int i = 0;
    log_file << "start .... " << endl;
    string old_line;
    while (compare(current_time, end_time)) // mỗi lần lặp là tăng thời gian lên 1h 18:00 -> 19:00 -> 1:00
    {
        // trong mỗi giờ mình sẽ xử lý.
        bool check_increment = true;
        log_file << "bat dau gio: " << i << endl;
        log_file << "old_line: " << old_line << endl;
        std::map<int, std::pair<int, double>> id_value; // id_count_value
        string line;
        DateTime start_time = (getHour(current_time));
        while (getline(filter2_2_, line)) // vòng lặp để đọc file
        {
            log_file << "readfile: " << line << endl;
            if (compare(stringToDate(string_to_time(line)), current_time)) // kiểm tra thỏa mãn điều kiện
            {
                log_file << "check file" << endl;

                /* code */
                if (id_value.count(extract_id(line)) == 0) // thêm vào map
                {
                    log_file << "chua co trong map" << endl;
                    if (old_line.size() != 0)
                    {
                        log_file << "co old_line " << endl;
                        if (extract_id(old_line) == extract_id(line))
                        {
                            log_file << "trung id" << endl;
                            id_value[extract_id(line)] = make_pair(2, extract_value(line) + extract_value(old_line));
                            log_file << "khoi tao: id =  " << extract_id(line) << ": " << 1 << ": " << extract_value(line) + extract_value(old_line) << endl;
                            old_line = "";
                        }
                        else
                        {
                            log_file << "khac id" << endl;
                            id_value[extract_id(line)] = make_pair(1, extract_value(line));
                            log_file << "khoi tao: id =  " << extract_id(line) << ": " << 1 << ": " << extract_value(line) << endl;

                            id_value[extract_id(old_line)] = make_pair(1, extract_value(old_line));
                            log_file << "khoi tao: id =  " << extract_id(line) << ": " << 1 << ": " << extract_value(old_line) << endl;
                            old_line = "";
                        }
                    }
                    else
                    {
                        log_file << "ko co old_line " << endl;
                        id_value[extract_id(line)] = make_pair(1, extract_value(line));
                        log_file << "khoi tao: id =  " << extract_id(line) << ": " << 1 << ": " << extract_value(line) << endl;
                    }
                }
                else // cập nhật lại count với value.
                {
                    log_file << "da co trong map" << endl;
                    // if (old_line.size() != 0)
                    // {
                    //     if (extract_value(old_line) == extract_value(line))
                    //     {
                    //         id_value[extract_id(line)].first += 2;
                    //         id_value[extract_id(line)].second += (extract_value(line) + extract_value(old_line));
                    //         old_line = "";
                    //     }
                    //     else
                    //     {
                    //         id_value[extract_id(line)].first += 1;
                    //         id_value[extract_id(line)].second += extract_value(line);

                    //         id_value[extract_id(old_line)].first += 1;
                    //         id_value[extract_id(old_line)].second += extract_value(line);
                    //         old_line = "";
                    //     }
                    // }
                    // else
                    {
                        // log_file << "tang count va value" << endl;
                        id_value[extract_id(line)].first += 1;
                        id_value[extract_id(line)].second += extract_value(line);
                    }
                }
            }
            else
            {
                old_line = line;
                current_time = addSeconds(current_time, 3600);
                check_increment = false;
                break;
            }
        }
        log_file << "xuat file" << endl;
        for (const auto &entry : id_value)
        {
            filter << entry.first << "," << setfill('0')
                   << setw(4) << start_time.year << ":" << setw(2) << start_time.month << ":" << setw(2) << start_time.day << " "
                   << setw(2) << start_time.hour << ":" << setw(2) << start_time.minute << ":" << setw(2) << start_time.second
                   << "," << std::fixed << std::setprecision(1) << entry.second.second / entry.second.first << task_2_2(roundToOneDecimal(entry.second.second / entry.second.first)) << endl;
        }
    
        if (check_increment)
        {
            current_time = addSeconds(current_time, 3600);
        }
        i++;
    }
    filter<<"endl";
}

int main()
{

    // sol(3, 50, 10);
    filter_("dust_sensor_test1.csv");
    sol_average("dust_sensor_test1.csv", "task2_2.csv", "result.txt");
}