#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <stack>
#include <sys/time.h>
#include <typeinfo>

std::stack<std::pair<int, double>> triangle_bucket(std::vector<std::pair<int, double>>, int, long int);

int main(void)
{
    struct timeval tv;
    
    //gettimeofday(&tv, NULL);
    
    //double time_begin = ((double)tv.tv_sec) * 1000 + ((double)tv.tv_sec) / 1000;

    std::vector<std::pair<int, double>> values;// {{1,5},{2,3},{5,1},{6,4},{9,6},{11,4},{13,3},{14,2},{18,5}};
    std::stack<std::pair<int, double>> values_of_return;
    long int i = 0;
    std::string str;
    double str1 = 0, y = 0;
    int x = 0;
    //int a;
    
    //unsigned w;
    //std::cout << sizeof(w) << std::endl;
    
    std::ifstream file("/home/l/code/cpp/data_qt_data_input.txt");

    while(!file.eof())//getline(file, str))
    {
        /*str = str.substr(str.find('\t'));
        a = str.find(',', 0);

        if(a >= 0)
            str[a] = '.';
        
        //str1 = 0;
        str1 = atof(str.c_str());
        values.push_back({i, str1});
        ++i;*/
        file >> x >> y;
        values.push_back({x, y});
        ++i;
    }

    file.close();

    /*std::ofstream file2("./data_qt_data_input.txt");

    for(int i = 0; i < values.size(); ++i)
    {
        //std::cout << values[i].first << ' ' << values[i].second << std::endl;
        file2 << values[i].first << ' ' << values[i].second << std::endl;
    }

    file2.close();*/
    
    gettimeofday(&tv, NULL);
    
    double time_begin = ((double)tv.tv_sec) * 1000 + ((double)tv.tv_usec) / 1000;

    values_of_return = triangle_bucket(values, 500, i);

    gettimeofday(&tv, NULL);
    
    double time_end = ((double)tv.tv_sec) * 1000 + ((double)tv.tv_usec) / 1000;

    //std::cout << std::endl;

    std::ofstream file1("/home/l/code/cpp/data_qt_data_output.txt");

    while(!values_of_return.empty())
    {
        //std::cout << values_of_return.top().first << ' ' << values_of_return.top().second << std::endl;
        file1 << values_of_return.top().first << ' ' << values_of_return.top().second << std::endl;
        values_of_return.pop();
    }

    file1.close();

    //gettimeofday(&tv, NULL);
    
    //double time_end = ((double)tv.tv_sec) * 1000 + ((double)tv.tv_sec) / 1000;
    double total_time_ms = time_end - time_begin;
    
    std::cout << total_time_ms << std::endl;
    std::system("~/code/python/plot.py");

    return 0;
}

std::stack<std::pair<int, double>> triangle_bucket(std::vector<std::pair<int, double>> values, int bucket_count, long int values_size)
{
    //int values_size = values.size();
    int size = (values_size - 2) / bucket_count;
    unsigned i = 0, j = 0, k = 0, t = 0;

    if(((values_size - 2) % bucket_count) > 0)
        ++bucket_count;
    
    std::stack<std::pair<int, double>> points;
    std::pair<double, double> mean_of_bucket {0, 0};
    //int j = 0, k = 0;
    double triangle_area = 0, area = 0, a_side = 0, b_side = 0, c_side, p = 0;//, d = 0;
    double a_line = 0, b_line = 0;

    points.push({values.front().first, values.front().second});
    //std::cout << points.top().first << ' ' << points.top().second << std::endl;
    for(i = 0; i < bucket_count; ++i)
    {
        mean_of_bucket.first = 0;
        mean_of_bucket.second = 0;

        t = (i + 1) * size + 1;

        for(j = t; j < t + size && j < values_size - 1; ++j)//, j < values_size - 1; ++j)
        {
            //if(j >= values_size - 1)
            //    break;
            mean_of_bucket.first += values[j].first;
            mean_of_bucket.second += values[j].second;
        }

        mean_of_bucket.first /= size;
        mean_of_bucket.second /= size;
        triangle_area = 0;
        int q = 0;

        t = i * size + 1;

        a_line = mean_of_bucket.first - points.top().first;
        b_line = mean_of_bucket.second - points.top().second;
        a_side = std::sqrt(a_line * a_line + b_line * b_line);
        //a_side = std::sqrt(std::pow(mean_of_bucket.first - points.top().first, 2) + std::pow(mean_of_bucket.second - points.top().second, 2));
        
        for(j = t; j < t + size && j < values_size - 1; ++j)//, j < values.size() - 1; ++j)
        {
            a_line = values[j].first - mean_of_bucket.first;
            b_line = values[j].second - mean_of_bucket.second;
            b_side = std::sqrt(a_line * a_line + b_line * b_line);

            a_line = values[j].first - points.top().first;
            b_line = values[j].second - points.top().second;
            c_side = std::sqrt(a_line * a_line + b_line * b_line);

            p = (a_side + b_side + c_side) / 2;
            area = std::sqrt(p * (p - a_side) * (p - b_side) * (p - c_side));
            
            if(area > triangle_area)
            {
                triangle_area = area;
                k = j;
            }

            //++q;
        }

        points.push({values[k].first, values[k].second});
        //std::cout << points.top().first << ' ' << points.top().second << ' ' << i << ' ' << q << std::endl;
    }

    points.push({values.back().first, values.back().second});

    return points;
}
