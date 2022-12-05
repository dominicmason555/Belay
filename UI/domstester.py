import sys
import time
import pynng
from qtpy import QtCore
from qtpy.QtCore import Qt, Slot, QThread
from qtpy.QtGui import QFont
from qtpy.QtWidgets import QApplication, QPushButton, QVBoxLayout, QWidget, QDialog, QLabel

from belay import belay_entry


ADDRESS = "tcp://127.0.0.1:5432"


class ServerThread(QThread):
    def run(self):
        belay_entry()


class MainWidget(QWidget):
    def __init__(self, sock):
        QWidget.__init__(self)
        self.setWindowTitle("Dom's Tester")
        self.sock = sock
        self.layout = QVBoxLayout(self)

        self.connecting_label = QLabel("Connecting, please wait...")
        self.connecting_label.setAlignment(QtCore.Qt.AlignCenter)
        self.layout.addWidget(self.connecting_label)

        self.cycle_button = QPushButton("Power Cycle")
        self.layout.addWidget(self.cycle_button)
        self.cycle_button.setShortcut("c")

        self.blink_button = QPushButton("Blink LED")
        self.layout.addWidget(self.blink_button)
        self.blink_button.setShortcut("b")

        sock.add_post_pipe_connect_cb(self.connected)
        sock.dial(ADDRESS, block=False)

        self.cycle_button.setEnabled(False)
        self.blink_button.setEnabled(False)
        self.cycle_button.clicked.connect(self.cycle_clicked)
        self.blink_button.clicked.connect(self.blink_clicked)

    @Slot()
    def cycle_clicked(self):
        print("Button: Power Cycle")
        sock.send("cycle".encode(), block=False)

    @Slot()
    def blink_clicked(self):
        print("Button: Blink LED")
        sock.send("blink".encode(), block=False)

    def connected(self, _):
        self.cycle_button.setEnabled(True)
        self.blink_button.setEnabled(True)
        self.connecting_label.setVisible(False)


if __name__ == "__main__":
    server_thread = ServerThread()
    server_thread.start()

    with pynng.Req0() as sock:
        app = QApplication(sys.argv)
        widget = MainWidget(sock)
        widget.resize(250, 150)
        widget.show()
        app.exit(app.exec_())

