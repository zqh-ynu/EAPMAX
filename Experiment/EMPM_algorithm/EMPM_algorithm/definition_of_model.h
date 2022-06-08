#pragma once
#ifndef PREDEFINE_H
#define PREDEFINE_H
#include<string>
#include<vector>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/vector.hpp> 
#include <boost/numeric/ublas/vector_proxy.hpp> 
#include <boost/numeric/ublas/matrix.hpp> 
#include <boost/numeric/ublas/triangular.hpp> 
#include <boost/numeric/ublas/lu.hpp> 
#include <boost/numeric/ublas/operation.hpp>
#include <limits.h>
#include <float.h>
#include <iomanip>
//#include <iostream>
#include <fstream>
#include<cstdlib>
#include<ctime>
using namespace std;
class User;
class Machine;


class User {
	// index i means user
protected:
	int a;	// the number of independent tasks known as a bag-of-tasks
	int index;		// the index of user
	double profit = 0;	// the profit of current user

public:
	User() { a = 0; index = 0; profit = 0; }
	User(int a_, int index_, double profit_) { a = a_; index = index_; profit = profit_; }
	void set_a(int a_) { a = a_; }
	void set_index(int index_) { index = index_; }
	void set_profit(double profit_) { profit = profit_; }

	int get_a() { return a; }
	int get_index() { return index; }
	double get_profit() { return profit; }
};

class Machine {
	// index j means machine
protected:
	int index;		// the index of machine

public:
	Machine() { index = 0; }
	Machine(int index_) { index = index_; }
	void set_index(int index_) { index = index_; }

	int get_index() { return index; }
};

class EAPMAX {	// energy-aware profit maximizing problem
protected:
	int m;							// the number of machine types 
	int n;							// the number of user types
	int current_user;				// the index of current user
	vector<User> users;				// the object of n usrs		
	vector<Machine> machines;		// the object of m machines

	// the three vectors will be reindexed by [i][jj] = [i][relabelled_index[i][j]] after relabel_index(); jj = relabelled_index[i][j]
	vector<vector<double>> ETC;		// estimated time to compute for a task of i on machine j, n×m
	vector<vector<double>> APC;		// average power consumption for a task of user i on machine j, n×m
	vector<double> L;				// the load (or finishing time) of machine j

	double MS;						// the maximum finishing time of all machines (i.e., makespan)
	double E;						// the energy consumed by n users
	double c = 1;						// the cost per unit of energy

	// sort the tasks of user i in descending order by APC_ij*ETC_ij, without loss of generality, assume that APC_i1*ETC_i1 ≥ APC_i2*ETC_i2 ≥...≥ APC_im*ETC_im, n×m
	vector<vector<int>> relabelled_index;

	/// <summary>
	/// each row of bottom vectors are indexed by [i][j]
	vector<vector<double>> ETCAPC;			// ETCAPC[i][j] = APC[i][j] * ETC[i][j];, n×m
	vector<vector<double>> x;				// the number of tasks of user i assigned to machine j, n×m
	// the first index of bottom three vectors named as X_i will be set to [ii][j] = [i + 1][j]
	vector<vector<double>> L_i;				// the load of machine j after assigning the tasks of the fist i users, (n+1)×m; // L_i[0][j]为机器j的初值，值为0；L_i[i][j],i=0~n共(n+1)个，所以L_i[i][j]代表第i个用户在机器j(0<=j<m)上的值
	vector<double> E_i;						// the total energy consumed after assigning the tasks of the first i users, 1×(n+1)
	vector<double> MS_i;					// the maximum finishing time of all machines (i.e., makespan) after assigning the tasks of the first i users, 1×n
	vector<vector<double>> Objective_value;	// the objective value for user i and guess tao


public:
	EAPMAX();						// constructor of class EAPMAX, all variables will be initialized 0 or null
	EAPMAX(int m_, int n_);			// constructor of class EAPMAX, m machines and n users, the size of all vector will be resized to m*n or m or n
	EAPMAX(string file_path);		// constructor of class EAPMAX, initializing related variables by the data from the file named "file_path"
	void init_relabelled_index();
	void caculate_ETCAPC();			// caculate the value of ETCAPC[i][j] = APC[i][j] * ETC[i][j];

	// sort the tasks of user i in descending order by APC_ij*ETC_ij, without loss of generality, assume that APC_i1*ETC_i1 ≥ APC_i2*ETC_i2 ≥...≥ APC_im*ETC_im
	void relabel_index(int i);
	void quickSort(vector<double>& a, int left, int right);
	void test_quickSort();
	template<class T>
	bool InvertMatrix(const boost::numeric::ublas::matrix<T>& input, boost::numeric::ublas::matrix<T>& inverse);
	int inversion_test();

	void Online_algorithm_for_EAPMAX();		// Our online algorithm
	void solve_linear_equations(int i, int tao, boost::numeric::ublas::matrix<double>& X_);			// Solving linear equations (15) in paper
	double caculate_objective_value(boost::numeric::ublas::matrix<double>& X, int i);

	void print_input_data();	// 在控制台输出通过文件输入的数据，包含了ETC，APC以及每个用户的任务数
	void print_ETC_all();
	void print_ETC_row(int i);
	void print_APC();
	void print_a();
	void print_ETCAPC_all();
	void print_ETCAPC_row(int i);
	void print_relabelled_index_all();
	void print_relabelled_index_row(int i);
	void print_x_all();
	void print_x_row(int i);
	void print_L_i_all();
	void print_L_i_row(int i);
	void print_E_i();
	void print_MS_i();
	void print_status(int i);			// print the system information after assined user i's tasks

};


#endif // PREDEFINE_H
