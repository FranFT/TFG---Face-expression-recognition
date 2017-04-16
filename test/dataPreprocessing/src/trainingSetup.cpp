#include <iostream>
#include <fstream>

using namespace std;

/**
 * It generates the solver file used for "bvlc_reference_caffenet"
 * @param _expr [description]
 */
void generateSolverFile( const string& _expr ){
  // Variables.
  ofstream solver_file;

  // Open file.
  solver_file.open( "solver.prototxt", ios::trunc );

  if( solver_file.is_open() ){
    solver_file
    << "net: \"buildDataPreprocessing/train_val.prototxt\"" << endl
    << "test_iter: 10" << endl
    << "test_interval: 25" << endl
    << "base_lr: 0.01" << endl
    << "lr_policy: \"step\"" << endl
    << "gamma: 0.05" << endl
    << "stepsize: 50" << endl
    << "display: 10" << endl
    << "max_iter: 200" << endl
    << "momentum: 0.9" << endl
    << "weight_decay: 0.0005" << endl
    << "snapshot: 250" << endl
    << "snapshot_prefix: \"/home/fran/Escritorio/results/yalefaces_train_"<< _expr << "\"" << endl
    //<< "snapshot_prefix: \"data/nets/yalefaces_train_"<< _expr << "\"" << endl
    << "solver_mode: CPU";

    solver_file.close();
  }
}

int main( int argc, char **argv ){
  /*
  Variables
  */
  string expresion;

  /*
  inicialitation
  */
  ( argc == 1 ) ? expresion = "all" : expresion = argv[1];

  generateSolverFile( expresion );

  return 0;
}
