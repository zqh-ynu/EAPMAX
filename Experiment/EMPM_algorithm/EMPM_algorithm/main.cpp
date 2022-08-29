#include "definition_of_model.h"


void one_example();
void print_to_csv(string path, vector<Result>& Online, vector<Result>& Greedy, vector<Result>& Average);
void print_x_to_csv(string path, string type, vector<vector<double>>& x);
void multiple_instances();

void variable_n();
void variable_gamma();
void case1_gamma_n30();
void case2_varaible_n();
void case3_bigsmall();


int inst_num = 50;
string data_root = "D:\\Myschool\\graduate_school\\02Graduate\\Research\\My paper\\EAPMAX\\Experiment\\EMPM_algorithm\\data\\";
string init_path = data_root + "profit1\\";
string produce_data_root = "D:\\Myschool\\graduate_school\\02Graduate\\Research\\My paper\\EAPMAX\\Experiment\\data\\";
string result_path = "D:\\Myschool\\graduate_school\\02Graduate\\Research\\My paper\\EAPMAX\\Experiment\\Result\\";
void main() {
	
	case1_gamma_n30();
	//case2_varaible_n();
	//case3_bigsmall();
}

void one_example() {
	string file_path = "D:\\Myschool\\graduate_school\\02Graduate\\Research\\My paper\\EAPMAX\\Experiment\\EMPM_algorithm\\data\\profit1\\";
	string test_file = file_path + "example.txt";
	EAPMAX test = EAPMAX(file_path, test_file);
	////test.test_quickSort();
	test.print_input_data();
	/*test.print_ETCAPC_all();
	test.print_relabelled_index_all();
	test.relabel_index();
	test.print_ETCAPC_all();
	test.print_relabelled_index_all();*/
	//test.inversion_test();
	/*test.relabel_index(0);
	for (int j = 0; j < 9; j++)
	{
		boost::numeric::ublas::matrix<double> X(10, 1, 0);

		test.solve_linear_equations(0, j, X);
	}*/
	test.set_gamma(1.5);
	test.set_profit();
	//test.print_profit();
	//Result Online;
	//test.Online_algorithm_for_EAPMAX(Online);

	Result Greedy;
	test.Greedy_based_method(Greedy);
}

void print_to_csv(string path, vector<Result>& Online, vector<Result>& Greedy, vector<Result>& Average)
{
	// 参数说明：
	//		path		csv文件保存的文件夹地址
	//		Online		vector列表，该实验的
	ofstream output;
	string obj_name = "obj_value.csv";
	string time_name = "time.csv";
	int len = Online.size();

	string opened_file = path + obj_name;
	cout << "\n" + opened_file;
	output.open(opened_file, ios::app);
	for (int i = 0; i < len; i++) {
		output << setprecision(7) << Online[i].get_objective_value() << ',' << Greedy[i].get_objective_value() << ',' << Average[i].get_objective_value() << '\n';

	}
	output.close();

	opened_file = path + time_name;
	cout << "\n" + opened_file;
	output.open(opened_file, ios::app);
	for (int i = 0; i < len; i++) {
		output << setprecision(7) << Online[i].get_time() << ',' << Greedy[i].get_time() << ',' << Average[i].get_time() << '\n';
	}
	output.close();
}

void print_x_to_csv(string path, string type, vector<vector<double>>& x)
{

	ofstream output;
	string opened_file = path + "x_" + type + ".csv";

	int n = x.size();
	int m = x[0].size();

	cout << "\n" + opened_file + "\n";
	output.open(opened_file, ios::app);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m - 1; j++)
		{
			output << x[i][j] << ',';
		}
		output << x[i][m - 1];
		output << '\n';
	}
	output.close();
}

void case1_gamma_n30()
{
	string case_path = produce_data_root + "case1_gamma_n30\\";
	string a = "";
	int ist_num = 100;
	double gamma[10] = {1.05, 1.1, 1.15, 1.2, 1.25, 1.3, 1.35, 1.4, 1.45, 1.5};
	string type[10] = {"gamma1", "gamma1_1", "gamma1_15", "gamma1_2", "gamma1_25", "gamma1_3", "gamma1_35", "gamma1_4", "gamma1_45", "gamma1_5" };
	vector<Result> Online;
	vector<Result> Greedy;
	vector<Result> Average;
	Online.resize(10);
	Greedy.resize(10);
	Average.resize(10);

	

	for (int i = 0; i < 10; i++)
	{
		std::cout << "\n------------------------------------------gamma = " << gamma[i] << " ------------------------------------------\n";
		for (int j = 0; j < ist_num; j++)
		{
			
			string ist_file = case_path + "ist" + to_string(j) + ".txt";
			//std::cout << "ist_file : " << ist_file << '\n';
			EAPMAX eapmax = EAPMAX(produce_data_root + "profit1//", ist_file);
			//eapmax.print_input_data();
			//eapmax.print_ETCAPC_all();

			eapmax.set_gamma(gamma[i]);
			eapmax.set_profit();
			//eapmax.print_profit();

			Result online_temp;
			Result greedy_temp;
			Result average_temp;
			eapmax.Online_algorithm_for_EAPMAX(online_temp);
			Online[i].add_result(online_temp);
			/*vector<vector<double>>& x = Online[i].get_x();
			std::cout << "\nn = " << x.size() << "\tm = " << x[0].size() << '\n';*/

			eapmax.Greedy_based_method(greedy_temp);
			Greedy[i].add_result(greedy_temp);
			//x = Greedy[i].get_x();

			eapmax.Average_based_method(average_temp);
			Average[i].add_result(average_temp);
			std::cout << "....................................istance " << j << " ....................................\n";
			std::cout << "online = " << online_temp.get_objective_value() << " greedy = " << greedy_temp.get_objective_value() << " average = " << average_temp.get_objective_value() << "\n";
		}
		
		Online[i].average(ist_num);
		Greedy[i].average(ist_num);
		Average[i].average(ist_num);

		//print_x_to_csv(result_path + "variable_30n_gamma\\" + "Online_x\\", type[i], x);
		//print_x_to_csv(result_path + "variable_30n_gamma\\" + "Greedy_x\\", type[i], x);
	}

	std::cout << "Online: \n";
	for (int i = 0; i < 10; i++)
	{
		Online[i].print_all();
	}
	std::cout << "Greedy: \n";
	for (int i = 0; i < 10; i++)
	{
		Greedy[i].print_all();
	}
	std::cout << "Average: \n";
	for (int i = 0; i < 10; i++)
	{
		Average[i].print_all();
	}
	// print_to_csv(result_path + "case1_gamma_n30\\", Online, Greedy, Average);
}

void case2_varaible_n() {
	string case_path = produce_data_root + "case2_variable_n\\";
	string a = "";
	int ist_num = 100;
	int N[5] = { 30, 100, 500, 1000, 2000 };
	double gamma[3] = { 1.2, 1.3, 1.5 };
	string sgamma[3] = { "1.2", "1.3", "1.5" };

	for (int g = 0; g < 3; g++) {
		std::cout << "\n------------------------------------------gamma = " << gamma[g] << " ------------------------------------------\n";
		vector<Result> Online;
		vector<Result> Greedy;
		vector<Result> Average;
		Online.resize(5);
		Greedy.resize(5);
		Average.resize(5);

		for (int i = 0; i < 5; i++) {
			std::cout << "\n-------------------------------------n = " << N[i] << " -------------------------------------\n";
			string case_n_path = case_path + "n" + to_string(N[i]) + "\\";
			for (int j = 0; j < ist_num; j++) {
				string ist_file = case_n_path + "ist" + to_string(j) + ".txt";
				//std::cout << "ist_file : " << ist_file << '\n';
				EAPMAX eapmax = EAPMAX(produce_data_root + "profit1//", ist_file);
				//eapmax.print_input_data();
				//eapmax.print_ETCAPC_all();

				eapmax.set_gamma(gamma[g]);
				eapmax.set_profit();
				//eapmax.print_profit();

				Result online_temp;
				Result greedy_temp;
				Result average_temp;
				eapmax.Online_algorithm_for_EAPMAX(online_temp);
				Online[i].add_result(online_temp);
				/*vector<vector<double>>& x = Online[i].get_x();
				std::cout << "\nn = " << x.size() << "\tm = " << x[0].size() << '\n';*/

				eapmax.Greedy_based_method(greedy_temp);
				Greedy[i].add_result(greedy_temp);
				//x = Greedy[i].get_x();

				eapmax.Average_based_method(average_temp);
				Average[i].add_result(average_temp);
				std::cout << "....................................istance " << j << " ....................................\n";
				std::cout << "online = " << online_temp.get_objective_value() << " greedy = " << greedy_temp.get_objective_value() << " average = " << average_temp.get_objective_value() << "\n";

			}

			Online[i].average(ist_num);
			Greedy[i].average(ist_num);
			Average[i].average(ist_num);
		}

		std::cout << "Online: \n";
		for (int i = 0; i < 5; i++)
		{
			Online[i].print_all();
		}
		std::cout << "Greedy: \n";
		for (int i = 0; i < 5; i++)
		{
			Greedy[i].print_all();
		}
		std::cout << "Average: \n";
		for (int i = 0; i < 5; i++)
		{
			Average[i].print_all();
		}
		print_to_csv(result_path + "case2_varaible_n\\" + "gamma" + sgamma[g] + "\\", Online, Greedy, Average);
	}
}

void case3_bigsmall() {
	string case_path = produce_data_root + "case3_bigsmall\\";
	int ist_num = 100;
	int n = 30;
	string type[4] = {"BaS", "SaB", "Rand", "Equal"};
	double gamma[3] = { 1.2, 1.3, 1.5 };
	string sgamma[3] = { "1.2", "1.3", "1.5" };

	for (int g = 0; g < 3; g++) {
		std::cout << "\n------------------------------------------gamma = " << gamma[g] << " ------------------------------------------\n";
		vector<Result> Online;
		vector<Result> Greedy;
		vector<Result> Average;
		Online.resize(4);
		Greedy.resize(4);
		Average.resize(4);

		for (int i = 0; i < 4; i++) {
			std::cout << "\n-------------------------------------" << type[i] << " -------------------------------------\n";
			string case_tp_path = case_path + type[i] + "\\";
			for (int j = 0; j < ist_num; j++) {
				string ist_file = case_tp_path + "ist" + to_string(j) + ".txt";
				std::cout << "ist_file : " << ist_file << '\n';
				EAPMAX eapmax = EAPMAX(produce_data_root + "profit1//", ist_file);
				//eapmax.print_input_data();
				//eapmax.print_ETCAPC_all();

				eapmax.set_gamma(gamma[g]);
				eapmax.set_profit();
				//eapmax.print_profit();

				Result online_temp;
				Result greedy_temp;
				Result average_temp;
				eapmax.Online_algorithm_for_EAPMAX(online_temp);
				Online[i].add_result(online_temp);
				/*vector<vector<double>>& x = Online[i].get_x();
				std::cout << "\nn = " << x.size() << "\tm = " << x[0].size() << '\n';*/

				eapmax.Greedy_based_method(greedy_temp);
				Greedy[i].add_result(greedy_temp);
				//x = Greedy[i].get_x();

				eapmax.Average_based_method(average_temp);
				Average[i].add_result(average_temp);
				std::cout << "....................................istance " << j << " ....................................\n";
				std::cout << "online = " << online_temp.get_objective_value() << " greedy = " << greedy_temp.get_objective_value() << " average = " << average_temp.get_objective_value() << "\n";

			}

			Online[i].average(ist_num);
			Greedy[i].average(ist_num);
			Average[i].average(ist_num);
		}

		std::cout << "Online: \n";
		for (int i = 0; i < 4; i++)
		{
			Online[i].print_all();
		}
		std::cout << "Greedy: \n";
		for (int i = 0; i < 4; i++)
		{
			Greedy[i].print_all();
		}
		std::cout << "Average: \n";
		for (int i = 0; i < 4; i++)
		{
			Average[i].print_all();
		}
		print_to_csv(result_path + "case3_bigsmall\\" + "gamma" + sgamma[g] + "\\", Online, Greedy, Average);
	}

}
