
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Utilities //////////////////////////////////////////////////////////////////////////////////////

string join(const vector<string>& v, const string& delim) {
    ostringstream s;
    for (const auto& i : v) {
        if (&i != &v[0]) {
            s << delim;
        }
        s << i;
    }
    return s.str();
}

vector<string> splitn( vector<string> &vec, const string &str, const char delimiter) {
  stringstream ss(str); // Turn the string into a stream.
  string tok;
  
  while(getline(ss, tok, delimiter)) {
    vec.push_back(tok);
  }
  
  return vec;
}

pair<string, string> split2(const string &str, const char delimiter) {
    string::size_type pos = str.find(delimiter);
    if(str.npos != pos) {
        auto k = str.substr(0, pos);
        auto v = str.substr(pos + 1);
        return make_pair(k, v);
    } else {
	    return make_pair(str, "");
    }
}