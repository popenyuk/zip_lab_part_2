import subprocess
import sys


def parse_result(result):
    time = 0
    to_return = False
    try:
        for i in result.split():
            if i == "Total:":
                to_return = True
            if to_return:
                try:
                    time = int(i)
                except:
                    pass
    finally:
        return str(time)


def read_from_file(name_of_file):
    with open(name_of_file, "r") as file:
        lines = file.readlines()
    result = dict()
    for line in lines:
        line = line.split()
        result[line[0]] = int(line[-1])
    return result

def is_equal(result1, result2):
    if type(result1) is not dict and type(result2) is not dict:
        return False

    # якщо їх довжини різні
    if len(result1) != len(result2):
        return False

    for keyword in result1:
        if keyword not in result2 or result1[keyword] != result2[keyword]:
            return False
    return True

def check_results(data):
    res_name = read_from_file("../result_by_name.txt")
    res_num = read_from_file("../result_by_number.txt")
    return is_equal(res_name, data[0]) and is_equal(res_num, data[1])


def run_one_time(file, input_file):
    process = subprocess.Popen([file, input_file], stdout=subprocess.PIPE)
    process.wait()
    res_name = read_from_file("../result_by_name.txt")
    res_num = read_from_file("../result_by_number.txt")
    return [res_name, res_num]


def run_solution(times, config, file):
    data = run_one_time(file, config)
    min_time = sys.maxsize
    results_are_same = True
    for _ in range(times):
        process = subprocess.Popen([file, config], stdout=subprocess.PIPE)
        process.wait()
        res = parse_result(process.stdout.read().decode('utf-8'))

        results_are_same = check_results(data)

        if int(res) < int(min_time):
            min_time = res
    print("Results of", file.split('_')[-2], file.split('_')[-1], ":")
    print("\tRunning time: " + min_time)
    if results_are_same:
        print("\tResults are the same for all the solutions runs\n")
    else:
        print("\tResults are NOT the same for all one solutions runs\n")
    return data


def main():
    if len(sys.argv) != 4 and len(sys.argv) != 3:
        print('Usage for multiple_thread: <program_name>'
              ' <times_to_run_the_program> <multiple/both> <configuration_file>')
        print('\nUsage for one_thread: <program_name> <times_to_run_the_program> <configuration_file>')
        exit(-1)

    one_thread = '../bin/_5_one_thread'
    multi_thread = '../bin/_5_multi_thread'

    times = int(sys.argv[1])
    if len(sys.argv) == 3:
        config = sys.argv[2]

        run_solution(times, config, one_thread)
        exit(-1)

    threads_to_run = sys.argv[2]
    config = sys.argv[3]

    if threads_to_run == 'multiple':
        run_solution(times, config, multi_thread)
    elif threads_to_run == 'both':
        first = run_solution(times, config, one_thread)
        second = run_solution(times, config, multi_thread)

        if first != second:
            print("Results are NOT the same for one thread and multiple threads solutions!")
        else:
            print("Results are the same for one thread and multiple threads solutions!")


if __name__ == '__main__':
    main()
