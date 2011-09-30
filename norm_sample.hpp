// Code generated by Stan version alpha.0

#include <cmath>
#include <vector>
#include <sstream>
#include <Eigen/Dense>
#include <stan/agrad/agrad.hpp>
#include <stan/agrad/special_functions.hpp>
#include <stan/agrad/matrix.hpp>
#include <stan/io/dump.hpp>
#include <stan/io/reader.hpp>
#include <stan/io/csv_writer.hpp>
#include <stan/maths/matrix.hpp>
#include <stan/maths/special_functions.hpp>
#include <stan/mcmc/hmc.hpp>
#include <stan/mcmc/sampler.hpp>
#include <stan/mcmc/prob_grad_ad.hpp>
#include <stan/prob/distributions.hpp>

namespace test_model {

using std::vector;
using std::string;
using std::stringstream;
using stan::agrad::var;
using stan::mcmc::prob_grad_ad;
using stan::io::dump;
using std::istream;

typedef Eigen::Matrix<double,1,Eigen::Dynamic> vector_d;
typedef Eigen::Matrix<double,Eigen::Dynamic,1> row_vector_d;
typedef Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> matrix_d;
typedef Eigen::Matrix<stan::agrad::var,1,Eigen::Dynamic> vector_v;
typedef Eigen::Matrix<stan::agrad::var,Eigen::Dynamic,1> row_vector_v;
typedef Eigen::Matrix<stan::agrad::var,Eigen::Dynamic,Eigen::Dynamic> matrix_v;

class test_model : public prob_grad_ad {
private:
    int M;
    int N;
public:
    test_model(std::istream& in__)
        : prob_grad_ad::prob_grad_ad(0) {
        dump dump__(in__);
        int pos;
        std::vector<int> vals_i;
        std::vector<double> vals_r;
        assert(dump__.contains_i("M"));
        vals_i = dump__.var_i_vals("M");
        pos = 0;
        M = vals_i[pos++];
        assert(dump__.contains_i("N"));
        vals_i = dump__.var_i_vals("N");
        pos = 0;
        N = vals_i[pos++];
    } // dump ctor

    var log_prob(vector<var>& params_r__,
                 vector<int>& params_i__) {

        var lp(0.0);
        // model parameters
        stan::io::reader<var> in__(params_r__,params_i__);

        vector<vector<var> > y;
        unsigned int dim_y_0 = M;
        y.resize(dim_y_0);
        for (unsigned int k_0 = 0; k_0 < dim_y_0; ++k_0) {
            unsigned int dim_y_1 = N;
            for (unsigned int k_1 = 0; k_1 < dim_y_1; ++k_1) {
                y[k_0].push_back(in__.scalar_constrain(lp));
            }
        }

        // derived variables

        // model body
        for (int m = 1; m <= M; ++m) {
            for (int n = 1; n <= N; ++n) {
                lp += stan::prob::normal_log(y[m - 1][n - 1], 0, 1);
            }
        }

        return lp;

    } // log_prob()

    void write_csv(std::vector<double>& params_r__,
                   std::vector<int>& params_i__,
                   std::ostream& o__) {
        stan::io::reader<double> in__(params_r__,params_i__);
        stan::io::csv_writer writer__(o__);
        vector<vector<double> > y;
        unsigned int dim_y_0 = M;
        y.resize(dim_y_0);
        for (unsigned int k_0 = 0; k_0 < dim_y_0; ++k_0) {
            unsigned int dim_y_1 = N;
            for (unsigned int k_1 = 0; k_1 < dim_y_1; ++k_1) {
                y[k_0].push_back(in__.scalar_constrain());
                writer__.write(y[k_0][k_1]);
            }
        }
    }

    void write_csv_header(std::ostream& o__) {
        stan::io::csv_writer writer__(o__);
        unsigned int bound_y_0 = M;
        unsigned int bound_y_1 = N;
        for (unsigned int i_y_0 = 0; i_y_0 < bound_y_0; ++i_y_0) {
            for (unsigned int i_y_1 = 0; i_y_1 < bound_y_1; ++i_y_1) {
                stringstream ss_y__;
                ss_y__ << "y[" << i_y_0 << ',' << i_y_1 << ',' << ']';
                writer__.write(ss_y__.str());
            }
        }
    }

}; // model

} // namespace

