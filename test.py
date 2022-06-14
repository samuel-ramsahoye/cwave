from build.module_name import *
from concurrent.futures import ThreadPoolExecutor
import time

start_time = time.time()

m = some_class_factory(1.0)
with ThreadPoolExecutor(4) as ex:
    ex.map(lambda x: m.function_that_takes_a_while(), [None]*4)

end_time = time.time()

print(end_time - start_time)