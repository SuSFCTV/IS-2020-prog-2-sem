#include "polynomial.h"
#include <algorithm>
//fixed constructor
Polynomial::Polynomial() {
    this->koef = new int;
    *this->koef = 0;
    this->deg = new int;
    *this->deg = 0;
    this->size = 1;
    this->min_d = 0;
    this->max_d = 0;
}

Polynomial::Polynomial(int min, int max, int *koefs) {
    int s = max - min + 1;
    this->size = s;
    this->min_d = min;
    this->max_d = max;
    int t = min;
    koef = new int[this->size];
    deg = new int[this->size];
    for (int i = 0; i < s; i++) {
        this->deg[i] = t;
        this->koef[i] = *koefs;
        t++;
        koefs++;
    }
}

Polynomial::Polynomial(const Polynomial &p) {
    this->size = p.size;
    koef = new int[this->size];
    deg = new int[this->size];
    this->min_d = p.deg[0];
    this->max_d = p.deg[size - 1];
    for (int i = 0; i < this->size; i++) {
        this->deg[i] = p.deg[i];
        this->koef[i] = p.koef[i];
    }
}

void Polynomial::resize_koef(int t_size, int bias){
    int *tmp = new int[t_size];
    for(int i = 0; i < t_size; i++){
        if(i >= bias && (i - bias) < this->size)
            tmp[i] = koef[i - bias];
    }
    delete [] koef;
    koef = tmp;
    this->size = t_size;
    min_d -= bias;
    max_d = min_d + this->size - 1;
}
//fixed "to do delete"
Polynomial::~Polynomial() {
    delete[] koef;
    delete[] deg;
};

Polynomial &Polynomial::operator=(const Polynomial &p) {
    min_d = p.min_d;
    max_d = p.max_d;
    size = p.size;
    delete[] koef;
    koef = new int[size];
    for (int i = 0; i < size; i++)
        koef[i] = p.koef[i];
    return *this;
}


bool Polynomial::operator==(const Polynomial &rhs) {
    stringstream ss_1, ss_2;
    ss_1 << *this;
    ss_2 << rhs;
    return ss_1.str() == ss_2.str();
};

bool Polynomial::operator!=(const Polynomial &rhs) {
    return !(*this == rhs);
};

Polynomial operator+(const Polynomial &lhs, const Polynomial &rhs) {
    int min = lhs.deg[0] <= rhs.deg[0] ? lhs.deg[0] : rhs.deg[0];
    int max = lhs.deg[lhs.size - 1] >= rhs.deg[rhs.size - 1] ? lhs.deg[lhs.size - 1] : rhs.deg[rhs.size - 1];
    int s = max - min + 1;
    int koef[s];
    int tmp_deg = min;
    for (int i = 0; i < s; i++) {
        koef[i] = 0;
        for (int j = 0; j < lhs.size; j++) {
            if (lhs.deg[j] == tmp_deg) {
                koef[i] += lhs.koef[j];
            }
        }
        for (int j = 0; j < rhs.size; j++) {
            if (rhs.deg[j] == tmp_deg) {
                koef[i] += rhs.koef[j];
            }
        }
        tmp_deg++;
    }

    return Polynomial(min, max, koef);
};

Polynomial operator-(const Polynomial &p) {
    int *temp = new int[p.size];
    for (int i = 0; i < p.size; i++)
        temp[i] = -p.koef[i];
    return Polynomial(p.min_d, p.max_d, temp);
};

Polynomial operator-(const Polynomial &lhs, const Polynomial &rhs) {
    return lhs + (-rhs);
};

Polynomial operator+=(Polynomial &lhs, const Polynomial &rhs) {
    lhs = lhs + rhs;
    return lhs;
};

Polynomial operator-=(Polynomial &lhs, const Polynomial &rhs) {
    lhs = lhs - rhs;
    return lhs;
};

//fixed for_each
Polynomial operator*(const Polynomial &p, int num) {
    int temp_koef[p.size];
    int i = 0;
    for_each(temp_koef, temp_koef + p.size, [num, p, &i](int &n) {
        n = p.koef[i] * num;
        i++;
    });
    return Polynomial(p.deg[0], p.deg[p.size - 1], temp_koef);
}

Polynomial operator*(int number, const Polynomial &p) {
    return p * number;
}

Polynomial operator*(const Polynomial &lhs, const Polynomial &rhs) {
    int tmp_size = (lhs.size) * (rhs.size);
    int tmp_koef[tmp_size], tmp_deg[tmp_size];
    int it = 0;

    for (int i = 0; i < lhs.size; i++) {
        for (int j = 0; j < rhs.size; j++) {
            tmp_koef[it] = lhs.koef[i] * rhs.koef[j];
            tmp_deg[it] = lhs.deg[i] + rhs.deg[j];
            it++;
        }
    }

    int min = tmp_deg[0];
    int max = tmp_deg[tmp_size - 1];
    int s = max - min + 1;
    int poly_deg[s], polynomial_koef[s];
    int tmp = min;

    for (int i = 0; i < s; i++) {
        poly_deg[i] = tmp;
        polynomial_koef[i] = 0;
        tmp++;
    }

    for (int i = 0; i < s; i++) {
        for (int j = 0; j < tmp_size; j++) {
            if (tmp_deg[j] == poly_deg[i]) {
                polynomial_koef[i] += tmp_koef[j];
            }
        }
    }

    return Polynomial(min, max, polynomial_koef);
};

Polynomial operator/(const Polynomial &p, int num) {
    int tmp_koef[p.size];
    for (int i = 0; i < p.size; i++) {
        tmp_koef[i] = p.koef[i] / num;
    }
    return Polynomial(p.deg[0], p.deg[p.size - 1], tmp_koef);
};

Polynomial operator*=(Polynomial &lhs, const Polynomial &rhs) {
    lhs = lhs * rhs;
    return lhs;
};

Polynomial operator/=(Polynomial &p, int num) {
    p = p / num;
    return p;
};

std::stringstream &operator<<(std::stringstream &out, const Polynomial &p) {
    int temp_size = p.size;
    if (temp_size == 1 and p.koef[0] == 0) {
        out << "0";
    } else {
        for (int i = temp_size - 1; i >= 0; i--) {
            if (p.koef[i] != 0) {
                if (i < temp_size - 1 && p.koef[i] > 0 && !out.str().empty() && out.str().back() != '\n') {
                    out << "+";
                }

                if (p.koef[i] == -1 && p.deg[i] != 0) {
                    out << "-";
                } else if (p.koef[i] == 1 && p.deg[i] != 0) {
                    out << "";
                } else {
                    out << p.koef[i];
                }

                if (p.deg[i] != 0) {
                    out << "x";
                    if (p.deg[i] != 1) {
                        out << "^" << p.deg[i];
                    }
                }

            }
        }
    }
    int temp = 0;
    for (int i = 0; i < p.size; i++) {
        if (p.koef[i] == 0) {
            temp++;
        }
    }
    if (temp == p.size && out.str().empty()) {
        out << "0";
    }
    return out;
}

Polynomial &operator>>(std::stringstream &fin, Polynomial &p) {
    string tmp = fin.str();
    bool num = false;
    int min = 0;
    int max = 0;
    string tmp_num;

    for (auto i = tmp.begin(); i != tmp.end(); i++) {
        if (*i == '^') {
            num = true;
            i++;
        }
        if (num) {
            tmp_num += *i;
        }

        if ((i + 1) == tmp.end() || *(i + 1) == '-' || *(i + 1) == '+'){
            break;
        }
    }
    istringstream(tmp_num) >> min;

    tmp_num.clear();

    for (auto i = tmp.end(); i != tmp.begin(); i--) {
        if (*i == '^') {
            while (i + 1 != tmp.end() && *(i + 1) != '-' && *(i + 1) != '+') {
                i++;
                tmp_num += *i;
            }
            break;
        }

    }
    istringstream(tmp_num) >> max;
    return p;
};

//fixed "to do return int"
int Polynomial::operator[](int num) const {
    if (num < min_d || num > max_d)
        return 0;
    return koef[num - min_d];
}

int &Polynomial::operator[](int num) {
    if (num < min_d || num > max_d) {
        int new_min = min(min_d, num);
        int new_max = max(max_d, num);
        int *mass = new int[new_max - new_min + 1];
        for (int i = 0; i < new_max - new_min + 1; i++) {
            mass[i] = 0;
        }
        Polynomial temp(new_min, new_max, mass);
        delete[] mass;

        *this += temp;
    }
    return koef[num - min_d];
}

//fixed O(n)
double Polynomial::get(double num) {
    double ans = 0;
    double x = pow(num, this->deg[0]);
    for (int i = 0; i < this->size; i++) {
        ans += this->koef[i] * x;
        x *= num;
    }
    return ans;
}

