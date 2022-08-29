import math

import numpy as np
import os
import random


def case1():
    # 生成随机顺序的30个用户的到达时间及其一包任务的任务数
    ist_num = 100  # 用例数
    n = 30
    file_path = "D:\\Myschool\\graduate_school\\02Graduate\\Research\\My " \
                "paper\\EAPMAX\\Experiment\\data\\case1_gamma_n30\\"

    for i_num in range(ist_num):
        Type = []
        for i in range(n):
            Type.append(i)
        random.shuffle(Type)
        print(Type)

        with open(file_path + "ist" + str(i_num) + ".txt", 'a') as f:
            s = "30\n"
            f.write(s)
            for i in range(n):
                task_num = random.randint(200, 1000)
                t = Type[i]

                s = "%d %d\n" % (t, task_num)
                f.write(s)
        f.close()

    pass


def case2():
    ist_num = 100
    N = [30, 100, 500, 1000, 2000]
    file_path = "D:\\Myschool\\graduate_school\\02Graduate\\Research\\My " \
                "paper\\EAPMAX\\Experiment\\data\\case2_variable_n\\"
    for n in N:
        case_file = file_path + "n" + str(n) + "\\"
        print(case_file)
        os.mkdir(case_file.rstrip("\\"))  # 创建目录时最后不能有\\
        for i_num in range(ist_num):
            Type = []
            for i in range(n):
                type_ = random.randint(0, 29)
                Type.append(type_)
            file_name = case_file + "ist" + str(i_num) + ".txt"
            print(file_name)
            with open(file_name, 'a') as f:
                s = str(n) + '\n'
                f.write(s)
                for i in range(n):
                    task_num = random.randint(200, 1000)
                    s = "%d %d\n" % (Type[i], task_num)
                    f.write(s)
            f.close()
    pass


def case3():
    ist_num = 100
    n = 30
    # 四种任务提交顺序，列表表示的是一包任务的任务数量
    Case_type = {
        "BaS": (500, 1000, 1, 200),
        "SaB": (1, 200, 500, 1000),
        "Rand": (1, 1000, 1, 1000),
        "Equal": (400, 400, 400, 400)
    }  # ["BaS", "SaB", "Rand", "Equal"]

    file_path = "D:\\Myschool\\graduate_school\\02Graduate\\Research\\My " \
                "paper\\EAPMAX\\Experiment\\data\\case3_bigsmall\\"

    for case_type in Case_type:  # 这样遍历字典，case_type的值是字典的索引
        # 该循环，每次生成100个该条件的实例文件，文件目录为case_file
        # 处理当前case的文件目录
        case_file = file_path + case_type + "\\"
        print(case_file)
        if not os.path.exists(case_file):
            os.mkdir(case_file.rstrip("\\"))

        for i_num in range(ist_num):
            # 该循环，每次能生成一个实例文件
            # 生成任务类型0~29
            Type = []
            for i in range(n):
                type_ = random.randint(0, 29)
                Type.append(type_)

            # 生成任务数量，大包任务数500~1000，小包任务数0~200
            task_num_range = Case_type[case_type]
            Task_num = []
            for i in range(n):
                if i < n / 2:
                    taskn = random.randint(task_num_range[0], task_num_range[1])
                else:
                    taskn = random.randint(task_num_range[2], task_num_range[3])
                Task_num.append(taskn)

            file_name = case_file + "ist" + str(i_num) + ".txt"
            with open(file_name, 'a') as f:
                s = str(n) + '\n'
                f.write(s)
                for i in range(n):
                    s = "%d %d\n" % (Type[i], Task_num[i])
                    f.write(s)
            f.close()


case1()
