import subprocess
import sys


def parse_result(result):
    return result.split(": ")[1]


def check_results(data):
    with open('../result/result_by_name.txt', 'r') as f:
        res_name = f.readlines()
    f.close()
    with open('../result/result_by_number.txt', 'r') as f:
        res_number = f.readlines()
    f.close()
    return res_name == data[0] and res_number == data[1]


def run_one_time(one_thread, input_file):
    subprocess.Popen([one_thread, input_file], stdout=subprocess.PIPE).communicate()[0].decode('utf-8')
    with open('../result/result_by_name.txt', 'r') as f:
        name = f.readlines()
    f.close()
    with open('../result/result_by_number.txt', 'r') as f:
        number = f.readlines()
    f.close()
    return [name, number]


def run_solution(times, config, file):
    data = run_one_time(file, config)
    min_time = sys.maxsize
    results_are_same = True
    for _ in range(times):
        process = subprocess.Popen([file, config], stdout=subprocess.PIPE)
        process.wait()
        res = parse_result(process.stdout.read().decode('utf-8'))

        if not check_results(data):
            results_are_same = False

        if int(res) < int(min_time):
            min_time = res

    print("Running time: " + min_time)
    if results_are_same:
        print("Results are the same for all the one solutions runs")
    else:
        print("Results are NOT the same for all the one solutions runs")
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
            print("\nResults are NOT the same for one thread and multiple threads solutions!")
        else:
            print("\nResults are the same for one thread and multiple threads solutions!")


if __name__ == '__main__':
    main()
