import time
import tracemalloc


class TimerMemory:  # pragma: no cover
    def __init__(self, print=False):
        self.time = None
        self.peak = None
        self.print = print

    def __enter__(self):
        self.start = time.perf_counter()
        tracemalloc.start()
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        current, peak = tracemalloc.get_traced_memory()
        tracemalloc.stop()
        time_passed = time.perf_counter() - self.start
        peak_in_MiB = peak / (1024 * 1024)
        peak_in_MB = peak / (1000 * 1000)
        peak_in_Mb = peak * 8 / (1000 * 1000)
        peak = peak_in_Mb
        if self.print:
            print(f"[Timer] Executed in {time_passed:.6f} seconds")
            print(f"[Memory] Used max {peak:.6f} Mb")
        self.time = time_passed
        self.peak = peak
