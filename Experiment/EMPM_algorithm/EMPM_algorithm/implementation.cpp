#include "definition_of_model.h"




/*
implementation of User class
*/



/*
implementation of Machine class
*/


/*
implementation of EAPMAX class
*/

EAPMAX::EAPMAX() {
	
}

EAPMAX::EAPMAX(int m_, int n_) {

}

EAPMAX::EAPMAX(string file_path) {
	m = 9;
	n = 30;
	current_user = 0;
	MS = 0;
	E = 0;
	c = 1;
	machines.resize(m);
	users.resize(n);

	ETC.resize(n);
	APC.resize(n);
	x.resize(n);
	L.resize(m);

	relabelled_index.resize(n);
	ETCAPC.resize(n);
	L_i.resize(n + 1);
	E_i.resize(n + 1);
	MS_i.resize(n);
	Objective_value.resize(n);

	for (int i = 0; i < n; i++)
	{
		ETC[i].resize(m);
		APC[i].resize(m);
		x[i].resize(m);
		relabelled_index[i].resize(m);
		ETCAPC[i].resize(m);
		L_i[i].resize(m);
		Objective_value[i].resize(m);
	}
	L_i[n].resize(m);

	for (int i = 0; i < n; i++)
	{
		users[i].set_index(i);
		E_i[i] = 0;
		MS_i[i] = 0;
		for (int j = 0; j < m; j++)
		{
			ETC[i][j] = 0;
			APC[i][j] = 0;
			x[i][j] = 0;
			ETCAPC[i][j] = 0;
			L_i[i][j] = 0;
			Objective_value[i][j] = 0;
		}
	}
	E_i[n] = 0;
	for (int j = 0; j < m; j++)
	{
		L_i[n][j] = 0;
		machines[j].set_index(j);
		L[j] = 0;
	}
	/// <summary>
	/// /////////////////////////
	/// </summary>
	/// <param name="file_path"></param>
	string data;
	string ETC_file = "ETC.csv";
	string APC_file = "APC.csv";
	string User_Num_file = "TPT.csv";
	char douhao;		// 在读取csv时，数字用逗号分隔，用该变量存储这个逗号
	std::ifstream fETC;

	fETC.open(file_path + ETC_file);
	std::cout << ETC.size() << '\n';
	// 读取ETC 30行9列
	for (int i = 0; i < n; i++)
	{
		getline(fETC, data);
		istringstream istr(data);
		//std::cout << data << '\n';
		for (int j = 0; j < m; j++)
		{
			istr >> ETC[i][j] >> douhao;
		}
	}
	fETC.close();

	std::ifstream fAPC;
	fAPC.open(file_path + APC_file);
	for (int i = 0; i < n; i++)
	{
		getline(fAPC, data);
		istringstream istr(data);
		//std::cout << data << '\n';
		for (int j = 0; j < m; j++)
		{
			istr >> APC[i][j] >> douhao;
		}
	}
	fAPC.close();
	
	std::ifstream fUnum;
	fUnum.open(file_path + User_Num_file);
	for (int i = 0; i < n; i++)
	{
		getline(fUnum, data);
		istringstream istr(data);
		int a;
		istr >> a;
		users[i].set_a(a);
	}
	fUnum.close();

	
	///////////////////////////////////////
	init_relabelled_index();
	caculate_ETCAPC();
}

void EAPMAX::init_relabelled_index()
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			relabelled_index[i][j] = j;
}

void EAPMAX::caculate_ETCAPC()
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			ETCAPC[i][j] = ETC[i][j] * APC[i][j];
}

void EAPMAX::set_profit()
{
	for (int i = 0; i < n; i++)
	{
		double E_min = ETCAPC[i][m - 1];
		double p = E_min * gamma;
		users[i].set_profit(p);
	}
}

void EAPMAX::quickSort(vector<double>& a, int left, int right)
{
	if (left >= right)
	{
		return;
	}

	int ii = left;
	int jj = right;
	int base = a[left];  //取最左边的数为基准数

	int base_index = relabelled_index[current_user][left];		// record the index of base user

	while (ii < jj)
	{
		while (a[jj] <= base && ii < jj)
		{
			jj--;
		}

		while (a[ii] >= base && ii < jj)
		{
			ii++;
		}

		if (ii < jj)
		{
			int temp = a[ii];
			a[ii] = a[jj];
			a[jj] = temp;

			temp = relabelled_index[current_user][ii];
			relabelled_index[current_user][ii] = relabelled_index[current_user][jj];
			relabelled_index[current_user][jj] = temp;
		}
	}
	//基准数归位
	a[left] = a[ii];
	a[ii] = base;

	relabelled_index[current_user][left] = relabelled_index[current_user][ii];
	relabelled_index[current_user][ii] = base_index;

	quickSort(a, left, ii - 1);//递归左边

	quickSort(a, ii + 1, right);//递归右边

}

void EAPMAX::test_quickSort() {
	vector<double> a;
	a.resize(10);

	relabelled_index.resize(1);
	relabelled_index[0].resize(10);
	for (int i = 0; i < 10; i++)
	{
		a[i] = rand();
		relabelled_index[0][i] = i;
	}

	cout << "a_before:\n ";
	for (int i = 0; i < 10; i++)
	{
		cout << a[i] << ' ';
	}
	cout << '\n';
	cout << "index_before:\n ";
	for (int i = 0; i < 10; i++)
	{
		cout << relabelled_index[0][i] << ' ';
	}
	cout << '\n';

	quickSort(a, 0, 9);

	cout << "a_after:\n ";
	for (int i = 0; i < 10; i++)
	{
		cout << a[i] << ' ';
	}
	cout << '\n';
	cout << "index_after:\n ";
	for (int i = 0; i < 10; i++)
	{
		cout << relabelled_index[0][i] << ' ';
	}
	cout << '\n';
}

void EAPMAX::relabel_index(int i) {
	current_user = i;
	quickSort(ETCAPC[i], 0, m - 1);
}


namespace ublas = boost::numeric::ublas;
template<class T>
bool EAPMAX::InvertMatrix(const ublas::matrix<T>& input, ublas::matrix<T>& inverse) {
	using namespace boost::numeric::ublas;
	typedef permutation_matrix<std::size_t> pmatrix;
	// create a working copy of the input 
	matrix<T> A(input);
	// create a permutation matrix for the LU-factorization 
	pmatrix pm(A.size1());
	// perform LU-factorization 
	int res = lu_factorize(A, pm);
	if (res != 0)
		return false;
	// create identity matrix of "inverse" 
	inverse.assign(ublas::identity_matrix<T>(A.size1()));
	// backsubstitute to get the inverse 
	lu_substitute(A, pm, inverse);
	return true;
}

int EAPMAX::inversion_test() {
	boost::numeric::ublas::matrix<double> m(5, 5);
	m(0, 0) = 1; m(0, 1) = 0; m(0, 2) = 0; m(0, 3) = 1; m(0, 4) = 1;
	m(1, 0) = 1; m(1, 1) = 1; m(1, 2) = 1; m(1, 3) = 0; m(1, 4) = 0;
	m(2, 0) = 1; m(2, 1) = 1; m(2, 2) = 0; m(2, 3) = 1; m(2, 4) = 0;
	m(3, 0) = 0; m(3, 1) = 0; m(3, 2) = 1; m(3, 3) = 0; m(3, 4) = 1;
	m(4, 0) = 0; m(4, 1) = 1; m(4, 2) = 1; m(4, 3) = 0; m(4, 4) = 1;
	std::cout << m << std::endl;
	boost::numeric::ublas::matrix<double> inversion(5, 5);
	bool inverted;
	inverted = InvertMatrix(m, inversion);
	std::cout << inversion << std::endl;
}

void EAPMAX::Online_algorithm_for_EAPMAX()
{

	for (int i = 0; i < n; i++)
		relabel_index(i);
	set_profit();
	//
	for (int i = 0; i < 10; i++)
	{
		int ii = i + 1;					// the first index of L_i, E_i, MS_i
		boost::numeric::ublas::matrix<double> best_X;		// best selution x_ij such that objective value is maximized
		double best_value = - DBL_MAX;
		int best_tao = 0;
		// ralabel the indices of tasks such that APC_i1*ETC_i1 ≥ APC_i2*ETC_i2 ≥...≥ APC_im*ETC_im
		relabel_index(i);

		////////////////////
		std::cout << "\n\n++++++++++++++++++++++++++++++++++++++ user" << i << " ++++++++++++++++++++++++++++++++++++++\n";
		print_ETCAPC_row(i);
		print_relabelled_index_row(i);

		for (int tao = 0; tao < m; tao++) {
			// solve equations(15) to find a solution x_ij^tao
			boost::numeric::ublas::matrix<double> X(10, 1, 0);
			solve_linear_equations(i, tao, X);
			// Comparing these M solution to find the best solution x_ij such that profit is the maximal
			double value = caculate_objective_value(X, i);
			
			std::cout << "\nvalue = " << value << ",\tbest_value = " << best_value;

			if (value > best_value)
			{
				best_value = value;
				best_tao = tao;
				best_X = X;
			}

			//// 输出猜测tao时的结果
			std::cout << "\ni = " << i << ",\ttao = " << tao << ",\ta = " << users[i].get_a() << ",\tMS_i = " << X(0, 0) << ",\tvalue = " << value << "\n";
			std::cout << X << "\n";
		}
		std::cout << "best_X: " << best_X <<'\n';
		std::cout << "best_X(0, 0): " << best_X(0, 0) <<'\n';
		
		for (int jj = 1; jj < m + 1; jj++)
		{
			x[i][jj - 1] = best_X(jj, 0);
			std::cout << "x" << i << "," << jj - 1 << "\tbest_X" << jj << "," << 0 << '\t' << best_X(jj, 0) << '\n';

		}
		std::cout << "x[" << i << "] = ";
		for (int j = 0; j < m; j++)
			std::cout << x[i][j] << " ";
		std::cout << '\n';

		int sum_x = 0;				// the sum of assined tasks of user i
		double xAPCETC = 0;			// the summary energy of assining tasks of user i
		for (int j = m - 1; j >= 0; j--)
		{
			int o = relabelled_index[i][j];
			// assign ^x_ij^ taks of type i to machines of type j, until all tasks are assigned;
			if (sum_x + x[i][o] < users[i].get_a())
			{
				x[i][o] = ceil(x[i][o]);			// 向上取整
				sum_x += x[i][o];
			}
			else
			{
				x[i][o] = users[i].get_a() - sum_x;
				sum_x += x[i][o];
			}
			xAPCETC += x[i][o] * ETCAPC[i][j];
			// update the average load of type j; L_i[j]

			L_i[ii][j] += (L_i[ii - 1][j] + x[i][j] * ETC[i][j]);
		}
		E_i[ii] += (E_i[ii - 1] + xAPCETC);
		for (int j = 0; j < m; j++)
			if (L_i[ii][j] > MS_i[ii])
				MS_i[ii] = L_i[ii][j];
		print_status(i);
	}
}

void EAPMAX::solve_linear_equations(int i, int tao, boost::numeric::ublas::matrix<double>& X_)
{
	// user i arrived and guess tao
	// i = 0 ~ (n - 1);		tao = 0 ~ (m - 1)
	// A × X = L   →   X = A^(-1) × L
	int dim = m - tao + 1;										// the dimension of matrix
	int ii = i + 1;												// the index of user in L_i, E_i and MS_i
	boost::numeric::ublas::matrix<double> A(dim, dim, 0);			// the coefficient matrix of linear equations
	boost::numeric::ublas::matrix<double> A_inverse(dim, dim, 0);	// the inverse matrix of A
	boost::numeric::ublas::matrix<double> L(dim, 1, 0);				// 
	boost::numeric::ublas::matrix<double> X(dim, 1, 0);				// 

	//////////////////////////
	// init A
	//////////////////////////
	std::cout << "-----\n";
	print_ETC_row(i);
	// init 1st row
	A(0, 0) = 0;
	for (int J = 1; J < dim; J++)
		A(0, J) = 1;
	for (int I = 1; I < dim; I++)
	{
		// I = 1 ~ (m - tao)
		int o = relabelled_index[i][tao + I - 1];	// 原序号
		A(I, 0) = 1;
		A(I, I) = - ETC[i][o];
	}
	// print A
	std::cout << "A:\n";
	for (int I = 0; I < dim; I++)
		std::cout << row(A, I) << '\n';


	//////////////////////////
	// init L
	//////////////////////////
	L(0, 0) = users[i].get_a();
	for (int J = 1; J < dim; J++)
	{
		int o = relabelled_index[i][tao + J - 1];
		L(J, 0) = L_i[ii - 1][o];
	}
	//print L
	std::cout << "L:\n" << L << '\n';


	//////////////////////////
	// get inverse matrix of A
	//////////////////////////
	InvertMatrix(A, A_inverse);
	// print A_inverse
	std::cout << "A_inverse:\n";
	for (int I = 0; I < dim; I++)
		std::cout << row(A_inverse, I) << '\n';


	//////////////////////////
	// X = A_inverse × L
	//////////////////////////
	axpy_prod(A_inverse, L, X);
	//print X
	std::cout << "X:\n" << X << '\n';
	X_(0, 0) = X(0, 0);
	for (int J = 1; J < dim; J++)
	{
		int o = relabelled_index[i][J + tao - 1];
		X_(o + 1, 0) = X(J, 0);
	}
	//print X
	std::cout << "X_:\n" << X_ << '\n';

	std::cout << "x*ETC:\n";
	for (int J = 1; J < m + 1; J++)
		std::cout << X_(J, 0) * ETC[i][J - 1] << '\t';
	std::cout << '\n';

	std::cout << "x*ETC + L_[i-1]:\n";
	for (int J = 1; J < m + 1; J++)
		std::cout << X_(J, 0) * ETC[i][J - 1] + L_i[ii - 1][J - 1 ] << '\t';
	std::cout << '\n';
}

double EAPMAX::caculate_objective_value(boost::numeric::ublas::matrix<double>& X, int i)
{
	// X 是原序索引
	int ii = i + 1;
	double p = 0;
	for (int I = 0; I < i + 1; I++)
	{
		p += users[I].get_a() * users[I].get_profit();
		// p += users[I].get_profit();
	}
	double xAPCETC = 0;
	for (int j = 0; j < m; j++)
	{
		int o = relabelled_index[i][j];
		if (X(o + 1, 0) >= 0)
		{
			xAPCETC += X(o + 1, 0) * ETCAPC[i][j];
		}
		else
		{
			xAPCETC = DBL_MAX;
			break;
		}
	}
	double MSi = X(0, 0);
	std::cout << "XXXXXXXXXXXXXX parameter XXXXXXXXXXXXXXXX\n";
	std::cout << "profit = " << p << "\tE_[i-1] = " << E_i[ii - 1] << "\txAPCETC = " << xAPCETC << "\tMSi = " << MSi << '\n';
	std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n";
	double objective_value = (p - c * E_i[ii - 1] - c * xAPCETC) / MSi;
	return objective_value;
}


void EAPMAX::print_input_data()
{
	std::cout << "m = " << m << ", n = " << n << "\n";
	print_a();
	print_ETC_all();
	print_APC();
	std::cout << "profit = " << users[0].get_profit() << '\n';
}

void EAPMAX::print_ETC_all()
{
	std::cout << "Estimated time to compute (ETC):\n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			std::cout << ETC[i][j] << '\t';
		std::cout << '\n';
	}
	std::cout << '\n';
}

void EAPMAX::print_ETC_row(int i)
{
	std::cout << "ETC" << i << " : ";
	for (int j = 0; j < m; j++)
		std::cout << ETC[i][j] << '\t';
	std::cout << '\n';
}

void EAPMAX::print_APC()
{
	std::cout << "Average power consumption (APC):\n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			std::cout << APC[i][j] << '\t';
		std::cout << '\n';
	}
	std::cout << '\n';
}

void EAPMAX::print_a()
{
	std::cout << "the tasks number of each user: ";
	for (int i = 0; i < n; i++)
		std::cout << users[i].get_a() << ' ';
	std::cout << '\n';
}

void EAPMAX::print_ETCAPC_all()
{
	std::cout << "ETC * APC:\n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			std::cout << ETCAPC[i][j] << '\t';
		std::cout << '\n';
	}
	std::cout << '\n';
}

void EAPMAX::print_ETCAPC_row(int i)
{
	std::cout << "ETCAPC" << i << " : ";
	for (int j = 0; j < m; j++)
		std::cout << ETCAPC[i][j] << '\t';
	std::cout << '\n';
}

void EAPMAX::print_relabelled_index_all()
{
	std::cout << "Relabelled index:\n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			std::cout << relabelled_index[i][j] << '\t';
		std::cout << '\n';
	}
	std::cout << '\n';
}

void EAPMAX::print_relabelled_index_row(int i)
{
	std::cout << "index_" << i << " : ";
	for (int j = 0; j < m; j++)
		std::cout << relabelled_index[i][j] << '\t';
	std::cout << '\n';
}

void EAPMAX::print_x_all()
{
	std::cout << "x:\n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			std::cout << x[i][j] << '\t';
		std::cout << '\n';
	}
	std::cout << '\n';
}

void EAPMAX::print_x_row(int i)
{
	std::cout << "x_" << i << " :\t";
	for (int j = 0; j < m; j++)
	{
		std::cout << x[i][j];
		if (x[i][j] < 1000)
			std::cout << "\t\t";
		else
			std::cout << '\t';
	}
	std::cout << '\n';
}

void EAPMAX::print_L_i_all()
{
	std::cout << "L_i:\n";
	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < m; j++)
		{
			std::cout << L_i[i][j];
			if (L_i[i][j] < 1000)
				std::cout << "\t\t";
			else
				std::cout << '\t';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

void EAPMAX::print_L_i_row(int i)
{
	std::cout << "L_" << i << " :\t";
	for (int j = 0; j < m; j++)
	{
		std::cout << L_i[i][j];
		if (L_i[i][j] < 1000)
			std::cout << "\t\t";
		else
			std::cout << '\t';
	}

	std::cout << '\n';
}

void EAPMAX::print_E_i()
{
	std::cout << "E_i:\n";
	for (int i = 0; i < n + 1; i++)
	{
		std::cout << E_i[i];
		if (E_i[i] < 1000)
			std::cout << "\t\t";
		else
			std::cout << '\t';
		if ((i + 1) % 10 == 0)
			std::cout << '\n';
	}
	std::cout << '\n';
}

void EAPMAX::print_MS_i()
{
	std::cout << "MS_i:\n";
	for (int i = 0; i < n + 1; i++)
	{
		std::cout << std::setprecision(3) << MS_i[i];
		if (MS_i[i] < 1000)
			std::cout << "\t\t";
		else
			std::cout << '\t';
		if ((i + 1) % 10 == 0)
			std::cout << '\n';
	}
	std::cout << '\n';
}

void EAPMAX::print_status(int i)
{
	std::cout << "\n########################### system status after assign user " << i << " ###########################\n";
	// x
	std::cout << "x:\n";
	for (int I = 0; I < i + 1; I++)
		print_x_row(I);
	// L_i
	std::cout << "L_i:\n";
	for (int I = 0; I < i + 2; I++)
		print_L_i_row(I);
	// x[i] * ETC[i]
	std::cout << "x * ETC:\n";
	for (int I = 0; I < i + 1; I++)
	{
		for (int j = 0; j < m; j++)
		{
			std::cout << x[I][j] * ETC[I][j];
			if (x[I][j] * ETC[I][j] < 1000)
				std::cout << "\t\t";
			else
				std::cout << '\t';
		}

		std::cout << '\n';
	}
	// E_i
	print_E_i();
	// MS_i
	print_MS_i();
}
