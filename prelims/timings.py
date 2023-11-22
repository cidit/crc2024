def timings(functions):
    import timeit
    import os

    if os.getenv("TIMEIT") == "TRUE":
        print("timings:")
        for f in functions:
            time = timeit.timeit(f, number=10_000)
            print(f"{f.__name__}, {time*1_000}ms")
