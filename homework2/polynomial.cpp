#include "polynomial.h"

Polynomial::Polynomial() {
    this->koef = (int *) malloc(sizeof(int));
    *this->koef = 0;

    this->deg = (int *) malloc(sizeof(int));
    *this->deg = 0;

    this->size = (int *) malloc(sizeof(int));
    *this->size = 1;
}

Polynomial::Polynomial(int min, int max, int *koef) {
    int s = max - min + 1;

    this->deg = (int *) malloc(s * sizeof(int));
    this->koef = (int *) malloc(s * sizeof(int));
    this->size = (int *) malloc(sizeof(int));
    *this->size = s;
    int t = min;

    for (int i = 0; i < s; i++) {
        this->deg[i] = t;
        this->koef[i] = *koef;
        t++;
        koef++;
    }
}

Polynomial::Polynomial(const Polynomial &p) {
    this->size = (int *) malloc(sizeof(int));
    *this->size = *p.size;

    this->koef = (int *) malloc((*this->size) * sizeof(int));
    this->deg = (int *) malloc((*this->size) * sizeof(int));

    for (int i = 0; i < *this->size; i++) {
        this->deg[i] = p.deg[i];
        this->koef[i] = p.koef[i];
    }
}

Polynomial::~Polynomial() = default;

Polynomial &Polynomial::operator=(const Polynomial &p) {
    this->koef = p.koef;
    this->deg = p.deg;
    this->size = p.size;
    return *this;
}

bool operator==(const Polynomial &lhs, const Polynomial &rhs) {
    stringstream ss_1, ss_2;
    ss_1 << lhs;
    ss_2 << rhs;
    return ss_1.str() == ss_2.str();
};

bool operator!=(const Polynomial &lhs, const Polynomial &rhs) {
    return !(lhs == rhs);
};

Polynomial operator+(const Polynomial &lhs, const Polynomial &rhs) {
    int min = lhs.deg[0] <= rhs.deg[0] ? lhs.deg[0] : rhs.deg[0];
    int max = lhs.deg[*lhs.size - 1] >= rhs.deg[*rhs.size - 1] ? lhs.deg[*lhs.size - 1] : rhs.deg[*rhs.size - 1];
    int s = max - min + 1;
    int koef[s];
    int tmp_deg = min;
    for (int i = 0; i < s; i++) {
        koef[i] = 0;
        for (int j = 0; j < *lhs.size; j++) {
            if (lhs.deg[j] == tmp_deg) {
                koef[i] += lhs.koef[j];
            }
        }
        for (int j = 0; j < *rhs.size; j++) {
            if (rhs.deg[j] == tmp_deg) {
                koef[i] += rhs.koef[j];
            }
        }
        tmp_deg++;
    }

    return Polynomial(min, max, koef);
};

Polynomial operator-(const Polynomial &p) {
    auto k = p;
    for (int i = 0; i < *k.size; i++) {
        k.koef[i] *= -1;
    }
    return k;
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

Polynomial operator*(const Polynomial &p, int num) {
    int tmp_koef[*p.size];
    for (int i = 0; i < *p.size; i++) {
        tmp_koef[i] = p.koef[i] * num;
    }
    return Polynomial(p.deg[0], p.deg[*p.size - 1], tmp_koef);
};

Polynomial operator*(int num, const Polynomial &p) {
    return p * num;
}

Polynomial operator*(const Polynomial &lhs, const Polynomial &rhs) {
    int tmp_size = (*lhs.size) * (*rhs.size);
    int tmp_koef[tmp_size], tmp_deg[tmp_size];
    int it = 0;

    for (int i = 0; i < *lhs.size; i++) {
        for (int j = 0; j < *rhs.size; j++) {
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
    int tmp_koef[*p.size];
    for (int i = 0; i < *p.size; i++) {
        tmp_koef[i] = p.koef[i] / num;
    }
    return Polynomial(p.deg[0], p.deg[*p.size - 1], tmp_koef);
};

Polynomial operator*=(Polynomial &lhs, const Polynomial &rhs) {
    lhs = lhs * rhs;
    return lhs;
};

Polynomial operator/=(Polynomial &p, int num) {
    p = p / num;
    return p;
};

std::stringstream &operator<<(std::stringstream &fout, const Polynomial &p) {
    int tmp_size = *p.size;
    int tmp = 0;
    if (tmp_size == 1 and p.koef[0] == 0) {
        fout << "0";
    } else {
        for (int i = tmp_size - 1; i >= 0; i--) {
            if (p.koef[i] != 0) {
                if (p.koef[i] > 0 && i < tmp_size - 1 && !fout.str().empty() && fout.str().back() != '\n') {
                    fout << "+";
                }

                if (p.koef[i] == -1 && p.deg[i] != 0) {
                    fout << "-";
                } else if (p.koef[i] == 1 && p.deg[i] != 0) {
                    fout << "";
                } else {
                    fout << p.koef[i];
                }

                if (p.deg[i] != 0) {
                    fout << "x";
                    if (p.deg[i] != 1) {
                        fout << "^" << p.deg[i];
                    }
                }

            }
        }
    }
    for (int i = 0; i < *p.size; i++) {
        if (p.koef[i] == 0) {
            tmp++;
        }
    }
    if (tmp == *p.size && fout.str().empty()) {
        fout << "0";
    }
    return fout;
};

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

int &Polynomial::operator[](int num) const {
    if (num > this->deg[0] && num < this->deg[*this->size - 1]) {
        int ind = 0;
        for (int i = 0; i < *this->size; i++) {
            if (num == this->deg[i]) {
                break;
            }
            ind++;
        }
        return this->koef[ind];
    } else {
        int *ans = new int;
        *ans = 0;
        return *ans;
    }
}

int &Polynomial::operator[](int num) {
    if (num > this->deg[0] && num < this->deg[*this->size - 1]) {
        const Polynomial p = *this;
        return p[num];
    } else if (num < this->deg[0]) {
        int min = num;
        int max = this->deg[*this->size - 1];
        int tmp_size = max - min + 1;
        int tmp_koef[tmp_size];
        for (int i = 0; i < tmp_size; i++) {
            tmp_koef[i] = 0;
        }

        for (int i = 1; i < *this->size; i++) {
            tmp_koef[tmp_size - i] = this->koef[*this->size - i];
        }

        *this = Polynomial(min, max, tmp_koef);
        return this->koef[0];
    } else {
        int min = this->deg[0];
        int max = num;
        int tmp_size = max - min + 1;
        int tmp_koef[tmp_size];

        for (int i = 0; i < tmp_size; i++) {
            tmp_koef[i] = 0;
        }

        for (int i = 0; i < *this->size; i++) {
            tmp_koef[i] = this->koef[i];
        }

        *this = Polynomial(min, max, tmp_koef);
        return this->koef[*this->size - 1];
    }
};

double &Polynomial::get(double num) {
    auto *ans = new double;
    *ans = 0;
    for (int i = 0; i < *this->size; i++) {
        *ans += this->koef[i] * pow(num, this->deg[i]);
    }
    return *ans;
}

