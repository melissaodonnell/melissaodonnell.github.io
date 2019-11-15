def main():

    count = int(input())

    while count > 0:

        problem = input()

        if problem == "P=NP":
            print("skipped")

        else:
            nums = problem.split("+")

            if len(nums) < 2:
                print("Invalid format.")

            else:
                sum = int(nums[0]) + int(nums[1])
                print(sum)

        count -= 1


    return 0


main()