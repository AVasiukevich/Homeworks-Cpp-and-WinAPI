#include<iostream>
#include<ctime>
#include<iomanip>

class DoubleMatrix
{
private:
	int col = 0;
	int row = 0;
	double** arr = nullptr;

public:
	friend std::ostream& operator<<(std::ostream& os, const DoubleMatrix& obj);

	friend std::istream& operator>>(std::istream& iss, DoubleMatrix& obj);

	DoubleMatrix() = default;

	DoubleMatrix(int col_, int row_)
		: arr{ new double*[row_] }, col{ col_ }, row{ row_ }
	{
		for (int i = 0; i < row; ++i)
			arr[i] = new double[col];
	}

	DoubleMatrix(const DoubleMatrix& obj)
		: DoubleMatrix(obj.col, obj.row)
	{
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				arr[i][j] = obj.arr[i][j];
			}
		}
	}

	DoubleMatrix(DoubleMatrix&& obj)
		: arr{ obj.arr }, col{ obj.col }, row{ obj.row }
	{
		obj.arr = nullptr;
		obj.col = 0;
		obj.row = 0;
	}

	const DoubleMatrix& operator=(const DoubleMatrix& obj)
	{
		if (this != &obj)
		{
			delete[] arr;
			arr = new double*[obj.row];
			for (int i = 0; i < row; ++i)
				arr[i] = new double[obj.col];
			col = obj.col;
			row = obj.row;
			for (int i = 0; i < row; ++i)
			{
				for (int j = 0; j < col; ++j)
				{
					arr[i][j] = obj.arr[i][j];
				}
			}
		}
		return *this;
	}

	DoubleMatrix& random(int random = 1)
	{
		if (random == 0)
		{
			std::cout << "Zero can not be used! Returned empty matrix!" << std::endl;
			random = 1;
		}
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				arr[i][j] = (double)(rand() % random * 0.01);
			}
		}
		return *this;
	}

	DoubleMatrix operator+(const DoubleMatrix& obj) const
	{
		DoubleMatrix t_mat(col, row);
		if (col == obj.col && row == obj.row) {
			for (int i = 0; i < row; ++i)
			{
				for (int j = 0; j < col; ++j)
				{
					t_mat.arr[i][j] = arr[i][j] + obj.arr[i][j];
				}
			}
			return t_mat;
		}
		else
			std::cout << "Matrixs size are not equal. Returned empty matrix!" << std::endl;

		return t_mat.random();
	}

	DoubleMatrix& operator+=(const DoubleMatrix& obj)
	{
		if (col == obj.col && row == obj.row)
			*this = *this + obj;
		else
			std::cout << "Invalid size. Returned to the original matrix!" << std::endl;

		return *this;
	}

	DoubleMatrix operator-(const DoubleMatrix& obj) const
	{
		DoubleMatrix t_mat(col, row);
		if (col == obj.col && row == obj.row) {
			for (int i = 0; i < row; ++i)
			{
				for (int j = 0; j < col; ++j)
				{
					t_mat.arr[i][j] = arr[i][j] - obj.arr[i][j];
				}
			}
			return t_mat;
		}
		else
			std::cout << "Matrixs size are not equal. Returned empty matrix!" << std::endl;

		return t_mat.random();
	}

	DoubleMatrix& operator-=(const DoubleMatrix& obj)
	{
		if (col == obj.col && row == obj.row)
			*this = *this - obj;
		else
			std::cout << "Invalid size. Returned to the original matrix!" << std::endl;

		return *this;
	}

	DoubleMatrix operator*(const DoubleMatrix& obj) const
	{
		DoubleMatrix t_mat(obj.col, row);
		t_mat.random();
		if (col == obj.row) {
			for (int i = 0; i < row; ++i)
			{
				for (int j = 0; j < obj.col; ++j)
				{
					for (int z = 0; z < col; ++z)
					{
						t_mat.arr[i][j] += arr[i][z] * obj.arr[z][j];
					}
				}
			}
			return t_mat;
		}
		else
			std::cout << "Matrix size are not equal. Returned empty matrix!" << std::endl;


		return t_mat;
	}

	DoubleMatrix& operator*=(const DoubleMatrix& obj)
	{
		if (col == obj.row)
			*this = *this * obj;
		else
			std::cout << "Matrix size are not equal. Returned to the original matrix!" << std::endl;

		return *this;
	}

	DoubleMatrix operator/(const DoubleMatrix& obj) const
	{
		DoubleMatrix t_mat(obj.col, row);
		if (obj.is_square() && obj.determeneit() != 0 && col == obj.row)
		{
			t_mat = *this * obj.reversMatrix();
			return t_mat;
		}
		else
			std::cout << "Matrixs size are not equal. Returned empty matrix!" << std::endl;

		return t_mat.random();
	}

	DoubleMatrix& operator/=(const DoubleMatrix& obj)
	{
		if (obj.is_square() && obj.determeneit() != 0 && col == obj.row)
			*this *= obj.reversMatrix();
		else
			std::cout << "Matrix size are not equal. Returned to the original matrix!" << std::endl;

		return *this;
	}

	DoubleMatrix operator/(double num) const
	{
		if (num == 0) {
			std::cout << "Can't divide by zero. Returned to the original matrix!" << std::endl;
			return *this;
		}
		else
			return *this *  (1 / num);
	}

	DoubleMatrix operator*(double num) const
	{
		DoubleMatrix t_mat(col, row);
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				t_mat.arr[i][j] = arr[i][j] * num;
			}
		}
		return t_mat;
	}

	DoubleMatrix& power(int pow)
	{
		if (this->is_square()) {
			if (pow == 0) {
				for (int i = 0; i < row; ++i)
				{
					for (int j = 0; j < col; ++j)
					{
						if (i == j)
							arr[i][j] = 1;
						else
							arr[i][j] = 0;
					}
				}
			}
			for (int i = 2; i <= pow; ++i)
				*this *= *this;
		}
		else
			std::cout << "Matrix size are not equal!" << std::endl;

		return *this;
	}

	double normRow() const 
	{
		double mNorm = 0, sum;
		for (int i = 0; i < row; ++i)
		{
			sum = 0;
			for (int j = 0; j < col; ++j)
			{
				sum += abs(arr[i][j]);
			}
			if (i == 0)
				mNorm = sum;
			else if (sum > mNorm)
				mNorm = sum;
		}
		return mNorm;
	}

	double normCol() const
	{
		double lNorm = 0, sum;
		for (int i = 0; i < row; ++i)
		{
			sum = 0;
			for (int j = 0; j < col; ++j)
			{
				sum += arr[j][i];
			}
			if (i == 0)
				lNorm = sum;
			else if (sum > lNorm)
				lNorm = sum;
		}
		return lNorm;
	}

	double normEuc() const
	{
		double eucNorm = 0;
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				eucNorm += pow(arr[j][i], 2);
			}
		}
		return sqrt(eucNorm);
	}

	bool is_square() const
	{
		return col == row;
	}

	bool is_zero() const
	{
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				if (arr[i][j] != 0)
					return false;
			}
		}
		return true;
	}

	bool is_diagonal() const
	{
		if (this->is_square()) {
			for (int i = 0; i < row; ++i)
			{
				for (int j = 0; j < col; ++j)
				{
					if (arr[i][j] != 0 && i != j)
						return false;
				}
			}
			return true;
		}
		return false;
	}

	bool is_unit() const
	{
		if (this->is_square()) {
			for (int i = 0; i < row; ++i)
			{
				for (int j = 0; j < col; ++j)
				{
					if (arr[i][j] != 0)
						if (arr[i][j] != 1 && i == j)
							return false;
				}
			}
			return true;
		}
		return false;
	}

	bool is_symmetry() const
	{
		if (this->is_square()) {
			for (int i = 0; i < row; ++i)
			{
				for (int j = 0; j < col; ++j)
				{
					if (i == j)
						continue;
					else if (arr[i][j] != arr[j][i])
						return false;
				}
			}
			return true;
		}
		return false;
	}

	bool is_lowT() const
	{
		if (this->is_square()) {
			for (int i = 0; i < row; ++i)
			{
				for (int j = i + 1; j < col; ++j)
				{
					if (arr[i][j] != 0)
						return false;
				}
			}
			return true;
		}
		return false;
	}

	bool is_topT() const
	{
		if (this->is_square()) {
			for (int i = 0; i < row; ++i)
			{
				for (int j = i + 1; j < col; ++j)
				{
					if (arr[j][i] != 0)
						return false;
				}
			}
			return true;
		}
		return false;
	}

	DoubleMatrix reversMatrix() const
	{
		double determ = this->determeneit();
		if (!is_square() || determ == 0) {
			std::cout << "Matrix size are not equal. Returned to the original matrix!" << std::endl;
			return *this;
		}

		DoubleMatrix rev_mat(col, col);
		DoubleMatrix minor(col - 1, col - 1);
		for (int j = 0; j < row * row; ++j)
		{
			for (int i = 0; i < col - 1; ++i)
			{
				for (int k = 0; k < col - 1; ++k)
				{
					if (i >= j % row && k >= j / row)
						minor.arr[k][i] = arr[k + 1][i + 1];
					else if (i >= j % row)
						minor.arr[k][i] = arr[k][i + 1];
					else if (k >= j / row)
						minor.arr[k][i] = arr[k + 1][i];
					else
						minor.arr[k][i] = arr[k][i];
				}
			}
			rev_mat.arr[j / row][j % row] = minor.determeneit() * pow(-1, (j / row + j % row));
		}
		return (rev_mat.transpositionMatrix() * (1 / determ));
	}

	DoubleMatrix transpositionMatrix() const
	{
		DoubleMatrix tranM(col, row);
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				tranM.arr[j][i] = arr[i][j];
			}
		}
		return tranM;
	}

	double determeneit() const
	{
		double determ = 0;
		if (!this->is_square())
		{
			std::cout << "Invalid size." << std::endl;
			return 0;
		}
		if (col == 1)
			return arr[0][0];
		else if (col == 2)
			return arr[0][0] * arr[1][1] - arr[0][1] * arr[1][0];

		DoubleMatrix minor(col - 1, col - 1);
		for (int j = 0; j < row; ++j)
		{
			for (int i = 0; i < col - 1; ++i)
			{
				for (int k = 0; k < col - 1; ++k)
				{
					if (i >= j)
						minor.arr[k][i] = arr[k][i + 1];
					else
						minor.arr[k][i] = arr[k][i];
				}
			}
			determ += pow(-1, col - 1 + j) * arr[col - 1][j] * minor.determeneit();
		}
		return determ;
	}

	bool operator==(const DoubleMatrix& obj) const
	{
		if (col != obj.col || row != obj.row)
			return false;
		else
		{
			for (int i = 0; i < row; ++i)
			{
				for (int j = 0; j < col; ++j)
				{
					if (arr[i][j] != obj.arr[i][j])
						return false;
				}
			}
		}
		return true;
	}

	bool operator!=(const DoubleMatrix& obj) const
	{
		return !operator==(obj);
	}

	~DoubleMatrix()
	{
		for (int i = 0; i < row; ++i)
			delete[] arr[i];
		delete[] arr;
	}
};

std::ostream& operator<<(std::ostream& os, const DoubleMatrix& obj)
{
	for (int i = 0; i < obj.row; ++i)
	{
		for (int j = 0; j < obj.col; ++j)
		{
			os << std::setw(5) << std::fixed << std::setprecision(2) << obj.arr[i][j] << "  ";
		}
		os << std::endl;
	}
	return os;
}

std::istream& operator>>(std::istream& is, DoubleMatrix& obj)
{
	std::cout << "Enter matrix[ " << obj.row << " ][ " << obj.col << " ]" << std::endl;
	for (int i = 0; i < obj.row; ++i)
	{
		for (int j = 0; j < obj.col; ++j)
		{
			std::cout << "[ " << i << " ][ " << j << " ] = ";
			is >> obj.arr[i][j];
		}
	}
	return is;
}

void menu()
{
	int par = 0, col = 0, row = 0;
	std::cout << "Enter size matrix ¹1: " << std::endl;
	std::cin >> row >> col;
	DoubleMatrix mat_1(row, col);
	std::cout << "Enter size matrix ¹2: " << std::endl;
	std::cin >> row >> col;
	DoubleMatrix mat_2(row, col);

	std::cout << "1. Create two matrices randomly?" << std::endl;
	std::cout << "2. Create two matrices manually?" << std::endl;
	std::cin >> par;
	switch (par)
	{
	case 1:
	{
		mat_1.random(1000);
		mat_2.random(1000);
		break;
	}
	case 2:
	{
		std::cout << "Creating matrices ¹1: " << std::endl;
		std::cin >> mat_1;
		std::cout << "Creating matrices ¹2: " << std::endl;
		std::cin >> mat_2;
		break;
	}
	default:
	{
		std::cout << "Invalid paragraph!" << std::endl;
		exit(1);
	}
	}

	system("cls");
	bool sw = true;
	while (sw)
	{
		std::cout << "Matrix ¹1:" << std::endl;
		std::cout << mat_1 << std::endl;
		std::cout << "Matrix ¹2:" << std::endl;
		std::cout << mat_2 << std::endl;
		std::cout << "Select the operation:" << std::endl;
		std::cout << "1. + " << std::endl;
		std::cout << "2. - " << std::endl;
		std::cout << "3. += " << std::endl;
		std::cout << "4. -= " << std::endl;
		std::cout << "5. * " << std::endl;
		std::cout << "6. * the number" << std::endl;
		std::cout << "7. *= " << std::endl;
		std::cout << "8. / " << std::endl;
		std::cout << "9. / the number " << std::endl;
		std::cout << "10. /= " << std::endl;
		std::cout << "11. == " << std::endl;
		std::cout << "12. != " << std::endl;
		std::cout << "13. Inverse matrix " << std::endl;
		std::cout << "14. Transposed matrix " << std::endl;
		std::cout << "15. Power matrix " << std::endl;
		std::cout << "16. Determinant" << std::endl;
		std::cout << "17. Norms matrix " << std::endl;
		std::cout << "18. Check the type of matrix " << std::endl;
		std::cout << "19. Exit program " << std::endl;

		std::cin >> par;
		system("cls");
		switch (par)
		{
		case 1:
		{
			std::cout << "Result:" << std::endl;
			std::cout << mat_1 + mat_2 << std::endl;
			break;
		}
		case 2:
		{
			std::cout << "Result:" << std::endl;
			std::cout << mat_1 - mat_2 << std::endl;
			break;
		}
		case 3:
		{
			std::cout << "Result:" << std::endl;
			std::cout << (mat_1 += mat_2) << std::endl;
			break;
		}
		case 4:
		{
			std::cout << "Result:" << std::endl;
			std::cout << (mat_1 -= mat_2) << std::endl;
			break;
		}
		case 5:
		{
			std::cout << "Result:" << std::endl;
			std::cout << mat_1 * mat_2 << std::endl;
			break;
		}
		case 6:
		{
			int par;
			std::cout << "Enter number: " << std::endl;
			std::cin >> par;
			std::cout << "Result:" << std::endl;
			std::cout << mat_1 * par << std::endl;
			break;
		}
		case 7:
		{
			std::cout << "Result:" << std::endl;
			std::cout << (mat_1 *= mat_2) << std::endl;
			break;
		}
		case 8:
		{
			std::cout << "Result:" << std::endl;
			std::cout << mat_1 / mat_2 << std::endl;
			break;
		}
		case 9:
		{
			int par;
			std::cout << "Enter number: " << std::endl;
			std::cin >> par;
			std::cout << "Result:" << std::endl;
			std::cout << mat_1 / par << std::endl;
			break;
		}
		case 10:
		{
			std::cout << "Result:" << std::endl;
			std::cout << (mat_1 /= mat_2) << std::endl;
			break;
		}
		case 11:
		{
			std::cout << "Result:" << std::endl;
			std::cout << std::boolalpha << (mat_1 == mat_2) << std::endl;
			break;
		}
		case 12:
		{
			std::cout << "Result:" << std::endl;
			std::cout << std::boolalpha << (mat_1 != mat_2) << std::endl;
			break;
		}
		case 13:
		{
			std::cout << "Result:" << std::endl;
			std::cout << mat_1.reversMatrix() << std::endl;
			break;
		}
		case 14:
		{
			std::cout << "Result:" << std::endl;
			std::cout << mat_1.transpositionMatrix() << std::endl;
			break;
		}
		case 15:
		{
			int par;
			std::cout << "Enter number: " << std::endl;
			std::cin >> par;
			std::cout << "Result:" << std::endl;
			std::cout << mat_1.power(par) << std::endl;
			break;
		}
		case 16:
		{
			std::cout << "Result:" << std::endl;
			std::cout << mat_1.determeneit() << std::endl;
			break;
		}
		case 17:
		{
			std::cout << "Result:" << std::endl;
			std::cout << "m - norm = " << mat_1.normRow() << std::endl;
			std::cout << "l - norm = " << mat_1.normCol() << std::endl;
			std::cout << "Euc. norm = " << mat_1.normEuc() << std::endl;
			break;
		}
		case 18:
		{
			std::cout << "Result:" << std::endl;
			std::cout << std::boolalpha << "Square matrix = " << mat_1.is_square() << std::endl;
			std::cout << std::boolalpha << "Diagonal matrix = " << mat_1.is_diagonal() << std::endl;
			std::cout << std::boolalpha << "Zero matrix = " << mat_1.is_zero() << std::endl;
			std::cout << std::boolalpha << "Unit matrix = " << mat_1.is_unit() << std::endl;
			std::cout << std::boolalpha << "Symmetric matrix = " << mat_1.is_symmetry() << std::endl;
			std::cout << std::boolalpha << "Low triangular matrix = " << mat_1.is_lowT() << std::endl;
			std::cout << std::boolalpha << "Top triangular matrix = " << mat_1.is_topT() << std::endl;
			break;
		}
		default: {sw = false; break; }
		}
	}
}

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	menu();

	return 0;
}