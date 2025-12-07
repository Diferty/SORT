import matplotlib.pyplot as plt
elements_count = []
bubble_time = []
piram_time = []



def on_key_press(event):
    print(f"Нажата клавиша: {event.key}")
    if event.key in ['q', 'escape']:
        file_graphics = open("graphics.txt", "r");
        while True:

            str = file_graphics.readline()
            if not str:
                break
            str = str.replace(',', '.')
            str_split = str.split(" ")
            elements_count.append(int(str_split[0]))
            bubble_time.append(int(float(str_split[1]) * 1000))
            piram_time.append(int(float(str_split[2]) * 1000))

        file_graphics.close()
        for i in range(len(elements_count)):
            for j in range(len(elements_count) - 1):
                if (elements_count[j] > elements_count[j + 1]):
                    elements_count[j], elements_count[j + 1] = elements_count[j + 1], elements_count[j]
                    bubble_time[j], bubble_time[j + 1] = bubble_time[j + 1], bubble_time[j]
                    piram_time[j], piram_time[j + 1] = piram_time[j + 1], piram_time[j]
while True:

    fig, ax = plt.subplots()
    ax.set_title("Нажмите 'q' или 'escape' для обновления")
    ax.plot(elements_count,bubble_time, label = "Сортировка Пузырьком")
    ax.plot(elements_count, piram_time, label="Пирамидальная сортировка")
    ax.set_xlabel('Количество Элементов')
    ax.set_ylabel('Время выполнения в мс')
    ax.legend()
    fig.canvas.mpl_connect('key_press_event', on_key_press)
    plt.show()
