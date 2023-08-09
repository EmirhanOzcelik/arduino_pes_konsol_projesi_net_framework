using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Konsol_arduino_hubdevice_sendkeys_
{
 
    public partial class Form1 : Form
    {
        int[] a = { 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, 115200 };
        public Form1()
        {
            InitializeComponent();
        }
        void yaz(String s) => textBox1.AppendText(s + Environment.NewLine);
        void al(String s ,int a)
        {
            if(a == 0)
            {
                textBox2.AppendText(s);
            }
            else
            {
                textBox2.AppendText(s + Environment.NewLine);
            }
        }
        void gonder(string s) => SendKeys.SendWait("{" + s + "}");
        private void comboBox1_Click(object sender, EventArgs e)
        {
            comboBox1.Items.Clear();
            String[] s = SerialPort.GetPortNames();
            foreach (String s2 in s)
            {
                comboBox1.Items.Add(s2);
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            CheckForIllegalCrossThreadCalls = false;
            textBox1.ReadOnly = true;
            textBox1.ScrollBars = ScrollBars.Both;
            textBox2.ReadOnly = true;
            textBox2.ScrollBars = ScrollBars.Both;
            textBox1.TabStop = false;  textBox2.TabStop = false;
            comboBox1.TabStop = false; comboBox2.TabStop = false;
            try
            {
                if (serialPort1.IsOpen)
                {
                    serialPort1.Close();
                }
            }catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                if (!serialPort1.IsOpen)
                {
                    if(comboBox2.SelectedItem != null)
                    {
                        serialPort1.BaudRate = a[comboBox2.SelectedIndex];
                    }
                    else
                    {
                        serialPort1.BaudRate = 115200;
                    }
                    if (comboBox1.SelectedItem == null)
                    {
                        serialPort1.PortName = "COM4";
                    }
                    else
                    {
                    serialPort1.PortName = comboBox1.SelectedItem.ToString();
                    }
                    serialPort1.Open();
                    yaz("Adres = " + serialPort1.PortName);
                    yaz("Baud Rate = " + serialPort1.BaudRate);
                    yaz("   ***   ");
                    button1.Text = "kes";
                    button1.BackColor = Color.Green;
                }
                else
                {
                    serialPort1.Close();
                    button1.Text = "bağlan";
                    button1.BackColor = Color.White;
                    yaz("bağlantı istemlice kesildi");
                    yaz("   ***   ");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            while (true)
            {
            string s = serialPort1.ReadLine();
            gonder(s);
            }

        }
    }
}
