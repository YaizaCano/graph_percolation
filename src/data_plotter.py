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


def plot_and_save(x, y, xLabel, yLabel, path):
    plt.xlabel(xLabel)
    plt.ylabel(xLabel)
    plt.plot(x, y)
    print('Saving plot', path)
    plt.savefig(path)
    plt.clf()

def plot_experiment(file_path, out_dir):
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
    plot_and_save(components, q_values, '#Components', 'q-prob',
                  os.path.join(out_dir, out_name) + "_components" )
    plot_and_save(difference, q_values, 'Difference', 'q-prob',
                  os.path.join(out_dir, out_name) + "_diifference")


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
        for file_name in os.listdir(file_dir):
            vars = file_name.split('_')
            plot_experiment(os.path.join(file_dir, file_name), out_dir)





if __name__ == '__main__':
    main()
