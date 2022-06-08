#include <ilcplex/ilocplex.h>
#include <stdio.h>
using namespace std;

ILOSTLBEGIN
//int main(void*)
//{
//	IloEnv env;
//	try {
//		IloModel model(env);
//		IloNumVarArray vars(env);
//		vars.add(IloNumVar(env, 0.0, 40.0));	//0 <= x1 <= 40
//		vars.add(IloNumVar(env));	// 0 <= x2
//		vars.add(IloNumVar(env));	// 0 <= x3
//		//maximize x1 + 2 x2 + 3 x3
//		model.add(IloMaximize(env, vars[0] + 2 * vars[1] + 3 * vars[2]));
//		model.add(-vars[0] + vars[1] + vars[2] <= 20);
//		model.add(vars[0] - 3 * vars[1] + vars[2] <= 30);
//		IloCplex cplex(model);
//		if (!cplex.solve()) {
//			env.error() << "Failed to optimize LP." << endl;
//			throw(-1);
//		}
//		IloNumArray vals(env);
//		env.out() << "Solution status = " << cplex.getStatus() << endl;
//		env.out() << "Solution value = " << cplex.getObjValue() << endl;
//		cplex.getValues(vals, vars);
//		env.out() << "Value = " << vals << endl;
//	}
//	catch (IloException& e) { cerr << "Concert exception caught:" << e << endl; }
//	catch (...) { cerr << "Unknuwn exception caught" << endl; }
//	env.end();
//	system("pause");
//	return 0;
//}