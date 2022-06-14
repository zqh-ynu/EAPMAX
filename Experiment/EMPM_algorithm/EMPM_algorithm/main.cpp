#include "definition_of_model.h"

void main() {
	string file_path = "D:\\Myschool\\graduate_school\\02Graduate\\Research\\My paper\\EAPMAX\\Experiment\\EMPM_algorithm\\data\\profit1\\";
	string test_file = file_path + "example.txt";
	EAPMAX test = EAPMAX(file_path);
	test.init_users_massage(test_file);
	////test.test_quickSort();
	test.print_input_data();
	//test.print_ETCAPC_all();
	//test.print_relabelled_index_all();
	//test.Online_algorithm_for_EAPMAX();
	//test.print_ETCAPC_all();
	//test.print_relabelled_index_all();
	//test.inversion_test();
	/*test.relabel_index(0);
	for (int j = 0; j < 9; j++)
	{
		boost::numeric::ublas::matrix<double> X(10, 1, 0);
		
		test.solve_linear_equations(0, j, X);
	}*/
	test.set_gamma(2);
	test.Online_algorithm_for_EAPMAX();

	

}

