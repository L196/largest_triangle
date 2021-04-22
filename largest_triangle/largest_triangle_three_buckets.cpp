#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <stack>

std::stack<std::pair<int, double>> triangle_bucket(std::vector<std::pair<int, double>>, int);

int main(void)
{
    std::vector<std::pair<int, double>> values;// {{1,5},{2,3},{5,1},{6,4},{9,6},{11,4},{13,3},{14,2},{18,5}};
    std::stack<std::pair<int, double>> values_of_return;
    int i = 0;
    std::string str;
    double str1;
    int a;

    std::ifstream file("./Data.txt");

    while(getline(file, str))
    {
        a = str.find(',', 0);

        if(a >= 0)
            str[a] = '.';

        str = str.substr(str.find('\t'));
        str1 = 0;
        str1 = atof(str.c_str());
        values.push_back({i, str1});
        ++i;
    }

    file.close();

    values_of_return = triangle_bucket(values, 300);

    std::cout << std::endl;

    std::ofstream file1("./data_qt_data12.txt");

    while(!values_of_return.empty())
    {
        std::cout << values_of_return.top().first << ' ' << values_of_return.top().second << std::endl;
        file1 << values_of_return.top().first << ' ' << values_of_return.top().second << std::endl;
        values_of_return.pop();
    }

    file1.close();
    
    return 0;
}

std::stack<std::pair<int, double>> triangle_bucket(std::vector<std::pair<int, double>> values, int bucket_count)
{
    int size = (values.size() - 2) / bucket_count, i = 0;

    if(((values.size() - 2) % bucket_count) > 0)
        ++bucket_count;
    
    std::stack<std::pair<int, double>> points;
    std::pair<double, double> mean_of_bucket {0, 0};
    int j = 0, k = 0;
    double triangle_area = 0, area = 0, a_side = 0, b_side = 0, c_side, p = 0, d = 0;

    points.push({values.front().first, values.front().second});
    //std::cout << points.top().first << ' ' << points.top().second << std::endl;
    for(i = 0; i < bucket_count; ++i)
    {
        mean_of_bucket.first = 0;
        mean_of_bucket.second = 0;

        for(j = (i + 1) * size + 1; j < (i + 2) * size + 1, j < values.size() - 1; ++j)
        {
            mean_of_bucket.first += values[j].first;
            mean_of_bucket.second += values[j].second;
        }

        mean_of_bucket.first /= size;
        mean_of_bucket.second /= size;
        triangle_area = 0;
        int q = 0;

        for(j = i * size + 1; j < (i + 1) * size + 1; ++j)//, j < values.size() - 1; ++j)
        {
            if(j >= values.size() - 1)
                break;

            a_side = std::sqrt(std::pow(mean_of_bucket.first - points.top().first, 2) + std::pow(mean_of_bucket.second - points.top().second, 2));
            b_side = std::sqrt(std::pow(values[j].first - mean_of_bucket.first, 2) + std::pow(values[j].second - mean_of_bucket.second, 2));
            c_side = std::sqrt(std::pow(values[j].first - points.top().first, 2) + std::pow(values[j].second - points.top().second, 2));
            p = (a_side + b_side + c_side) / 2;
            area = std::sqrt(p * (p - a_side) * (p - b_side) * (p - c_side));
            
            if(area > triangle_area)
            {
                triangle_area = area;
                k = j;
            }

            ++q;
        }

        points.push({values[k].first, values[k].second});
        std::cout << points.top().first << ' ' << points.top().second << ' ' << i << ' ' << q << std::endl;
    }

    points.push({values.back().first, values.back().second});

    return points;
}