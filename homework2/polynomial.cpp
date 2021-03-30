#include "polynomial.h"
#include <algorithm>

//fixed "weird constructor"
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
    koef = new int[s];
    deg = new int[s];
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

//fixed destructor
Polynomial::~Polynomial() {
    delete[] koef;
    delete[] deg;
};

Polynomial &Polynomial::operator=(const Polynomial &p) {
    min_d = p.min_d;
    max_d = p.max_d;
    size = p.size;
    delete[] koef;
    delete[] deg;
    koef = new int[size];
    deg = new int[size];
    for (int i = 0; i < size; i++) {
        koef[i] = p.koef[i];
        deg[i] = p.deg[i];
    }

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

//fixed +/+=
Polynomial operator+(const Polynomial &lhs, const Polynomial &rhs) {
    Polynomial new_pol{lhs};
    return new_pol += rhs;
};

Polynomial Polynomial::operator+=(const Polynomial &p) {
    int min = this->deg[0] <= p.deg[0] ? this->deg[0] : p.deg[0];
    int max = this->deg[this->size - 1] >= p.deg[p.size - 1] ? this->deg[this->size - 1] : p.deg[p.size - 1];
    int temp_size = max - min + 1;
    int temp_koef[temp_size];
    int temp_deg = min;
    for (int i = 0; i < temp_size; i++) {
        temp_koef[i] = 0;
        for (int j = 0; j < this->size; j++) {
            if (this->deg[j] == temp_deg) {
                temp_koef[i] += this->koef[j];
            }
        }
        for (int j = 0; j < p.size; j++) {
            if (p.deg[j] == temp_deg) {
                temp_koef[i] += p.koef[j];
            }
        }
        temp_deg++;
    }

    *this = Polynomial(min, max, temp_koef);
    return *this;
}

Polynomial operator-(const Polynomial &p) {
    int *temp = new int[p.size];
    for (int i = 0; i < p.size; i++)
        temp[i] = -p.koef[i];
    return Polynomial(p.min_d, p.max_d, temp);
};

Polynomial operator-(const Polynomial &lhs, const Polynomial &rhs) {
    return lhs + (-rhs);
};


Polynomial operator-=(Polynomial &lhs, const Polynomial &rhs) {
    lhs = lhs - rhs;
    return lhs;
};

//fixed for_each
Polynomial operator*(const Polynomial &lhs, int num) {
    Polynomial new_p { lhs };
    for_each(new_p.koef, new_p.koef + new_p.max_d - new_p.min_d + 1, [&](int &n){n *= num;});
    return new_p ;
}

Polynomial operator*(int num, const Polynomial &p) {
    return p * num;
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
    int tmp = min;
    int s = max - min + 1;
    int poly_deg[s], pol_koef[s];

    for (int i = 0; i < s; i++) {
        poly_deg[i] = tmp;
        pol_koef[i] = 0;
        tmp++;
    }

    for (int i = 0; i < s; i++) {
        for (int j = 0; j < tmp_size; j++) {
            if (tmp_deg[j] == poly_deg[i]) {
                pol_koef[i] += tmp_koef[j];
            }
        }
    }

    return Polynomial(min, max, pol_koef);
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

        if ((i + 1) == tmp.end() || *(i + 1) == '-' || *(i + 1) == '+') {
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


int Polynomial::operator[](int num) const {
    if (num < min_d || num > max_d)
        return 0;
    return koef[num - min_d];
}

int &Polynomial::operator[](int num) {
    if (num < min_d || num > max_d) {
        int t_min = min(min_d, num);
        int t_max = max(max_d, num);
        int *koefs = new int[t_max - t_min + 1];
        for (int i = 0; i < t_max - t_min + 1; i++) {
            koefs[i] = 0;
        }
        Polynomial temp(t_min, t_max, koefs);
        delete[] koefs;

        *this += temp;
    }
    return koef[num - min_d];
}

//fixed "to do O(n)"
double Polynomial::get(double number) {
    double ans = 0;
    double tmp = pow(number, this->deg[0]);
    for (int i = 0; i < this->size; i++) {
        ans += this->koef[i] * tmp;
        tmp *= number;
    }
    return ans;
}

