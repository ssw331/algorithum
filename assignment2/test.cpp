#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>

clock_t start_,end_;

using namespace std;

bool searchMatrix(vector<vector<int> >& matrix, int target){
        //TODO
	int m = matrix.size(), n = matrix[0].size();
	int s_m = m - 1, s_n = 0;
	while (s_m >= 0 && s_n < n)
	{
		if (matrix[s_m][s_n] > target)
			s_m--;
		else if (matrix[s_m][s_n] < target)
			s_n++;
		else
			return 1;
	}
	return 0;
	int l_m = 0, r_m = m - 1, mid_m = r_m;
	int l_n = 0, r_n = n - 1, mid_n = (l_n + r_n) / 2;
	while (mid_n < n && mid_m >= 0)
	{
		while (matrix[mid_m][mid_n] > target && mid_m >=0)
		{
			r_n = mid_n - 1;
			mid_n = (l_n + r_n) / 2;
			if (l_n > r_n && mid_m > 0)
				mid_m--, r_n = n - 1;
			else if (mid_m <= 0)
				return 0;
		}
		if (matrix[mid_m][mid_n] == target)
			return 1;
		else
			mid_n++, l_n = mid_n;
		if (mid_n >= n - 1)
			return 0;
		while (matrix[mid_m][mid_n] < target && mid_n < n)
		{
			l_m = mid_m + 1;
			mid_m = (l_m + r_m) / 2;
			if (l_m > r_m && mid_n < n - 1)
				mid_n++, l_m = 0;
			else if (mid_n >= n - 1)
				return 0;
		}
		if (matrix[mid_m][mid_n] == target)
			return 1;
		else
			mid_m--, r_m = mid_m;
		if (mid_m <= 0)
			return 0;
	}
	return 0;
	//双重折半查找
}


int main(){
	
//	读取测试数据 
    ifstream inFile("testcase.csv", ios::in);
    string lineStr;
    
    start_ = clock();
    

	if (!inFile.is_open())
	{
		cout<<"Error!"<<endl;
	}
	
//	测试结果标记
	int correct_num = 0;
	int error_num = 0;
	

//	运行测试数据，输出结果 
    while (getline(inFile, lineStr))
    {
    	vector<vector<int>> matrix;
		
    	string number;
    	bool num_end = false;
    	bool line_end = false;
    	int target = -1;
    	bool result;
    	vector<int> line;
    	for(int i=0; i<lineStr.size(); i++){
    		if (!num_end){
	    		if (lineStr[i] == '['){
	    			line_end = false;
	    			line.clear();
				}
				else if (lineStr[i] == ']' && line_end){
					number = "";
					num_end = true;
				}
	    		else if (lineStr[i] == ']' && !num_end){
	    			line.push_back(atoi(number.c_str()));
	    			matrix.push_back(line);
	    			line_end = true;
	    			number = "";
				}
				
				else if (lineStr[i] >= '0' && lineStr[i] <= '9')number += lineStr[i];
				else if (lineStr[i] == ',' && !line_end){
					line.push_back(atoi(number.c_str()));
					number = "";
				}
			}
			else{
				if (target == -1){
					if (lineStr[i] >= '0' && lineStr[i] <= '9')number += lineStr[i];
					else if (lineStr[i] == ',' && number != "")target = atoi(number.c_str());
				}
				else result = lineStr[i]-'0';
			}
		}
		if (result == searchMatrix(matrix,target))correct_num += 1;
		else error_num += 1;
	}
	end_ = clock();
	double endtime = (double)(end_ - start_)/CLOCKS_PER_SEC;
	inFile.close();
	
	cout<<"correct:"<<correct_num<<endl;
	cout<<"error:"<<error_num<<endl;
	cout<<"用时:"<<endtime*1000<<"ms"<<endl;
	
	system("pause");
	
	return 0;
}
