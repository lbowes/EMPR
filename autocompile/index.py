print("Welcome to autocompiler :)")
path = input("Can I have the path please: ")
project = input("What do you want me to compile if you want project say project else playground: ")

import time
from watchdog.observers import Observer
from watchdog.events import PatternMatchingEventHandler
import os
import subprocess
recompiling=False

def recompile(event):
    global recompiling
    if not recompiling:
        recompiling=True
        subprocess.run(f"cd {path}/{project} && make complete", shell=True)
        print("Change detected compiling")
        time.sleep(10)
        recompiling=False
def empty():
    pass
    


if __name__ == "__main__":
    patterns = "*"
    ignore_patterns = ""
    ignore_directories = False
    case_sensitive = True
    my_event_handler = PatternMatchingEventHandler(patterns, ignore_patterns, ignore_directories, case_sensitive)
    my_event_handler.on_created = recompile
    my_event_handler.on_deleted = recompile
    my_event_handler.on_modified = recompile
    my_event_handler.on_moved = recompile
    my_observer = Observer()
    my_observer.schedule(my_event_handler, path, recursive=True)
    my_observer.start()
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        my_observer.stop()
        my_observer.join()