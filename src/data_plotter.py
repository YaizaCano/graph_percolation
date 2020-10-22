import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import sys
import os

# constants definition
GEOMETRIC_GRAPH = 'geometric'
GRID2D = 'grid2d'
COMPONENTS_COL = 'components'
Q_COL = 'q'
DIFF_COL = 'difference'

# auxiliar function

def get_name(path):
    return ''.join(path.split('/')[-1].split('.')[:-1])


# define plot functions


def plot_and_save(x, y, xLabel, yLabel, path, title, label, annotate=False):
    plt.title(title)
    plt.xticks(np.linspace(0, 1, 11))
    plt.xlabel(xLabel)
    plt.ylabel(yLabel)

    if annotate:
        max_arg = y.argmax()
        max_y = y[max_arg]
        max_x = x[max_arg]
        plt.annotate(" q = " + "(" + str(max_x) + ")", (max_x, max_y))
        min_arg = y.argmin()
        min_y = y[min_arg]
        min_x = x[min_arg]
        plt.annotate(" q = " + "(" + str(min_x) + ")", (min_x, min_y))
    plt.plot(x, y, label=label)
    print('Saving plot', path)
    #plt.savefig(path)
    #plt.clf()


def derivate(x, y):
    z = [0] * len(x)

    for i in range(2, len(x)):
        z[i - 1] = (y[i] - y[i - 2]) / (x[i] - x[i - 2])
    z[-1] = z[-2]
    return np.array(z)



def plot_experiment(file_path, out_dir, label=None):
    """
    Generates a plot for the given experiment. It generates a
    2D plot where the y axis represents the q value and x axis the
    number of connected components

    Parameters:
        file_path: the file of the experiment
        out_dir: path of where to save the plot
    """
    data = pd.read_csv(file_path)
    q_values = sorted(list(set(data['q'])))
    pairs = []
    for val in q_values:
        cols = data.loc[data['q'] == val].mean()
        pairs.append([cols[COMPONENTS_COL], cols[DIFF_COL]])
    pairs = np.array(pairs)
    components = pairs[:, 0]
    difference = pairs[:, 1]
    # plot components graph
    out_name = get_name(file_path)
    plot_and_save(q_values, components, 'q-prob', '#Components',
                  os.path.join(out_dir, out_name) + "_components", out_name.split('_')[0] + " Components", label)
    #plot_and_save(q_values, derivate(q_values, components), 'q-prob', 'Derivative',
    #              os.path.join(out_dir, out_name) + "_derivative", out_name.split('_')[0] + " Derivative")
    #plot_and_save(q_values, derivate(q_values, derivate(q_values, components)), 'q-prob', 'Second Derivative',
    #              os.path.join(out_dir, out_name) + "_sderivative", out_name.split('_')[0] + " Second Derivative")


def usage():
    """
    Define the usage of the app
    """
    print('\nUsage:  python data_plotter file_dir out_dir\n')
    print('    file_dir: the directory where experiments are stored')
    print('    out_dir: the directory where to save the plots\n')


# main function
def main():

    if len(sys.argv) != 3:
        usage()
    else:
        print("Intitializing...")
        file_dir = sys.argv[1]
        out_dir = sys.argv[2]
        print('Opening directory', file_dir)
        # open each file and create a plot per file
        # each plot is independent since we are not
        # interested in comparing graphs but in finding
        # phase transition points
        for file_name in sorted(os.listdir(file_dir)):
            vars = file_name.split('_')
            if vars[0] == GEOMETRIC_GRAPH:
                plot_experiment(os.path.join(file_dir, file_name), out_dir, str(vars[1])[:4])
        plt.legend(bbox_to_anchor=(1,1), loc="upper left")
        plt.gcf().subplots_adjust(right=0.8)
        plt.savefig(os.path.join(out_dir, "components_geometric.png"))





if __name__ == '__main__':
    main()
