#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;

void InitSuperBlock();  // 初始化超级块
void InitUI();  // 初始化用户界面
void AllocateBlock(int size);  // 分配空闲块
void ReleaseBlock(vector<int> file);  // 释放空闲块
void PrintFile();  // 打印文件
void PrintFreeBlock();  // 打印当前所有空闲块
void Refactor();  // 重构成组链接空闲块

struct FreeBlock {
	bool isLeader;  // 是否为组长块
	int p[50];  // 作为组长块时使用，用于存放前一组的块号
	int size;  // 作为组长块时使用，前一组块数
	int seq;  // 空闲块的序号
	bool isFree;  // 是否空闲
	int data[15];  // 数据域，用于存放数据
	FreeBlock() {
		isLeader = false;
		size = 0;
		isFree = true;
	}
};
FreeBlock **block;

int a[51];  // 超级块，a[0]存储栈深
int totalGroups;  // 成组链接总组数
int group;  // 当前所在的组号
int num;  // 空闲块总块数
int remain;  // 空闲块剩余块数
vector<vector<int>> files;  // 文件

int main() {
	srand(unsigned(time(0)));
	num = rand() % 101 + 300;  // 随机300~400个空闲块
	cout << "随机空闲块总块数：" << num << endl;
	int tmp = num + 1;  // 第一组只有49块，加上1块便于计算，实际上没有
	// 申请空闲块二维数组
	totalGroups = (tmp % 50) == 0 ? tmp / 50 : (tmp / 50 + 1);
	block = new FreeBlock *[totalGroups];
	block[0] = new FreeBlock[49];
	for (int i = 1; i < totalGroups; i++) {
		block[i] = new FreeBlock[50];
	}
	tmp--;
	// 建立空闲块成组链接
	for (int i = 0; i < totalGroups; i++) {
		for (int j = 0; j < 50; j++) {
			if (tmp == 0) {
				break;
			}
			if (j == 0 && i != 0) {  // 组长块
				for (int k = 0; k < 50; k++) {
					if (i == 1) {  // 特殊处理第二组
						if (k == 0) {
							block[i][0].p[k] = 0;
						}
						else {
							block[i][0].p[k] = block[i - 1][k - 1].seq;
						}
						continue;
					}
					block[i][0].p[k] = block[i - 1][k].seq;
				}
				block[i][0].isLeader = true;
				block[i][0].size = 50;
				block[i][0].seq = tmp;
				tmp--;
			}
			else {  // 普通空闲块
				if (i == 0 && j == 49) {  // 第一组只有49块
					break;
				}
				block[i][j].seq = tmp;
				tmp--;
			}
		}
	}
	group = totalGroups - 1;  // 当前所在组的组号
	remain = num;

	InitSuperBlock();  // 初始化超级块
	InitUI();  // 初始化用户界面

	return 0;
}

// 初始化超级块
void InitSuperBlock() {
	int n = 0;  // 记录最后一组空闲块的个数（可能不足50）
	for (int i = 0; i < 50; i++) {
		if (block[group][i].seq < 0 || !block[group][i].isFree) {
			break;
		}
		n++;
		a[i + 1] = block[group][i].seq;
	}
	a[0] = n;
}

// 初始化用户界面
void InitUI() {
	while (1) {
		int x;
		int filesSize = files.size();
		cout << "***********************************************************************************" << endl;
		cout << "* 1.空闲块分配   2.空闲块释放   3.查看文件   4.查看空闲块   5.重构空闲块   6.退出 *" << endl;
		cout << "***********************************************************************************" << endl;
		cout << "请输入操作：";
		cin >> x;
		if (x == 1) {  // 空闲块分配
			cout << "当前分配的是第" << filesSize + 1 << "个文件！" << endl;
			while (1) {
				cout << "请输入文件需要的空闲块个数：";
				int n;
				cin >> n;
				if (n <= 0) {
					cout << "错误：输入错误！" << endl;
					continue;
				}
				if (n > remain) {
					cout << "错误：剩余空闲块块数为" << remain << "。无法分配！" << endl << endl;
					break;
				}
				remain -= n;  // 剩余空闲块减少
				AllocateBlock(n);
				break;
			}
		}
		else if (x == 2) {  // 空闲块释放
			if (filesSize == 0) {
				cout << "当前文件为空！" << endl << endl;
			}
			else {
				while (1) {
					cout << "请输入要释放的文件号：";
					int n;
					cin >> n;
					if (n <= 0 || n > filesSize) {
						cout << "错误：输入错误！" << endl;
						continue;
					}
					remain += files[n - 1].size();  // 剩余空闲块增加
					ReleaseBlock(files[n - 1]);
					// 释放后删除
					for (vector<vector<int>>::iterator it = files.begin(); it != files.end(); it++) {
						if (*it == files[n - 1]) {
							files.erase(it);
							break;
						}
					}
					break;
				}
			}
		}
		else if (x == 3) {  // 查看文件
			if (filesSize == 0) {
				cout << "当前文件为空！" << endl << endl;
			}
			else {
				PrintFile();
			}
		}
		else if (x == 4) {  // 查看空闲块
			PrintFreeBlock();
		}
		else if (x == 5) {  // 重构空闲块
			Refactor();
		}
		else if (x == 6) {  // 退出
			exit(0);
		}
		else {  // 其它
			cout << "错误：输入无效，请重新输入！" << endl << endl;
		}
	}
}

// 空闲块分配
void AllocateBlock(int size) {
	vector<int> f;
	cout << "分配空闲块：";
	for (int i = 0; i < size; i++) {
		if (a[0] == 1) {  // 组长块
			if (a[a[0]] == 0) {
				cout << "警告！！空闲块不足！";
				break;
			}
			int t = a[1];  // 组长块最后也用来存储
			block[group][0].isLeader = false;  // 不再是组长块
			block[group][0].isFree = false;  // 不再是空闲
			a[0] = block[group][0].size;  // 超级块栈深
			block[group][0].size = 0;
			for (int j = 0; j < 50; j++) {
				a[j + 1] = block[group][0].p[j];
			}
			group--;
			f.push_back(t);
			cout << t << " ";
		}
		else {  // 普通空闲块
			if (a[1] == 0) {  // 最后一组特殊处理
				block[group][a[0] - 2].isFree = false;  // 不再是空闲
			}
			else {
				block[group][a[0] - 1].isFree = false;  // 不再是空闲
			}
			f.push_back(a[a[0]]);
			cout << a[a[0]] << " ";
			a[0]--;
		}
	}
	files.push_back(f);
	cout << endl << endl;
}

// 空闲块释放
void ReleaseBlock(vector<int> file) {
	int fileSize = file.size();
	cout << "释放为空闲块：";
	for (int i = fileSize - 1; i >= 0; i--) {
		if (a[0] == 50) {
			group++;
			block[group][0].isLeader = true;  // 组长块
			block[group][0].isFree = true;
			block[group][0].size = 50;
			block[group][0].seq = file[i];
			for (int j = 0; j < 50; j++) {
				block[group][0].p[j] = a[j + 1];
			}
			a[0] = 1;
			a[a[0]] = file[i];  // 释放
			cout << a[a[0]] << " ";
		}
		else {
			if (a[1] == 0) {  // 特殊处理最后一组
				block[group][a[0] - 1].isFree = true;
				block[group][a[0] - 1].seq = file[i];
			}
			else {
				block[group][a[0]].isFree = true;
				block[group][a[0]].seq = file[i];
			}
			a[0]++;
			a[a[0]] = file[i];
			cout << a[a[0]] << " ";
		}
	}
	cout << endl << endl;
}

// 打印所有已分配有空闲块的文件
void PrintFile() {
	int filesSize = files.size();
	for (int i = 0; i < filesSize; i++) {
		int size = files[i].size();
		cout << "文件" << (i + 1) << "分配的块数量为" << size << "，块号分别为：";
		for (int t : files[i]) {
			cout << t << " ";
		}
		cout << endl;
	}
	cout << endl;
}

// 打印当前所有空闲块
void PrintFreeBlock() {
	if (remain == 0) {
		cout << "当前空闲块块数为0！" << endl << endl;
		return;
	}
	cout << "第1组：" << endl << "普通空闲块：";
	for (int i = 0; i <= group; i++) {
		for (int j = 0; j < 50; j++) {
			if (i == 0 && j == 49) {
				break;
			}
			if (block[i][j].isLeader) {
				cout << endl << "第" << i + 1 << "组：" << endl;
				cout << "组长块:" << block[i][j].seq << "( 成员块：";
				for (int k = 0; k < 50; k++) {
					cout << block[i][j].p[k] << " ";
				}
				cout << ")" << endl << "普通空闲块：";
			}
			else {
				if ((i == group && j >= a[0]) || !block[i][j].isFree) {
					break;
				}
				cout << block[i][j].seq << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}

// 重构成组链接空闲块
void Refactor() {
	vector<int> ivec;
	vector<int>::iterator it;
	// 收集所有块号
	for (int i = 0; i <= group; i++) {
		for (int j = 0; j < 50; j++) {
			if ((i == group && j >= a[0]) || (i == 0 && j == 49)) {
				break;
			}
			ivec.push_back(block[i][j].seq);
		}
	}
	ivec.push_back(0);
	sort(ivec.begin(), ivec.end());
	it = ivec.end() - 1;
	// 重构
	for (int i = 0; i <= group; i++) {
		for (int j = 0; j < 50; j++) {
			if (j == 0 && i != 0) {  // 组长块
				for (int k = 0; k < 50; k++) {
					if (i == 1) {  // 特殊处理第二组的组长块
						if (k == 0) {
							block[i][0].p[k] = 0;
						}
						else {
							block[i][0].p[k] = block[i - 1][k - 1].seq;
						}
						continue;
					}
					block[i][0].p[k] = block[i - 1][k].seq;
				}
				block[i][0].isLeader = true;
				block[i][0].size = 50;
				block[i][0].seq = *it;
				it--;
			}
			else {  // 普通空闲块
				if (i == 0 && j == 49) {
					break;
				}
				block[i][j].seq = *it;
				it--;
			}
			// 排序时把0也算进去排，刚好用来结束
			if (it == ivec.begin()) {
				break;
			}
		}
	}
	InitSuperBlock();  // 初始化超级块
	cout << "重构完成！！" << endl << endl;
}

