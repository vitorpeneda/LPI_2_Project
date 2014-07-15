using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using PortaSerie;
using System.IO.Ports;


namespace WeatherStation
{

    public partial class Form1 : Form
    {
        string savedPath, COM;

        public Form1()
        {
            InitializeComponent();

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private bool Read_File(string path)
        {

            const int data_lenght = 86;

            string data = " ", trama = "";
            try
            {
                StreamReader file = new StreamReader(path);

                while (file.EndOfStream == false)
                {
                    data = file.ReadLine();
                }
                // MessageBox.Show(data.Length.ToString());

                if (data.Length == data_lenght)
                {
                    for (int i = data.IndexOf('D') + 2; i < 14; i++)
                    {
                        trama += data[i];
                    }
                    textBox1.Text = trama;
                    trama = "\n";
                    for (int i = data.IndexOf('C') + 2; i < 24; i++)
                    {
                        trama += data[i];
                    }
                    textBox12.Text = trama;
                    trama = "\n";
                    for (int i = data.IndexOf('S') + 2; i < 34; i++)
                    {
                        trama += data[i];
                    }
                    textBox2.Clear();
                    textBox2.Text = trama;
                    trama = "\n";
                    for (int i = data.IndexOf('W') + 2; i < 39; i++)
                    {
                        trama += data[i];
                    }
                    textBox3.Text = trama;
                    trama = "\n";
                    for (int i = data.IndexOf('A') + 2; i < 45; i++)
                    {
                        trama += data[i];
                    }
                    textBox13.Text = trama;
                    trama = "\n";
                    for (int i = data.IndexOf('R') + 2; i < 54; i++)
                    {
                        trama += data[i];
                    }
                    textBox4.Text = trama;
                    trama = "\n";
                    for (int i = data.IndexOf('H') + 2; i < 62; i++)
                    {
                        trama += data[i];
                    }
                    textBox5.Text = trama;
                    trama = "\n";
                    for (int i = data.IndexOf('T') + 2; i < 73; i++)
                    {
                        trama += data[i];
                    }
                    textBox6.Text = trama;
                    trama = "\n";
                    for (int i = data.IndexOf('P') + 2; i < 83; i++)
                    {
                        trama += data[i];
                    }
                    textBox7.Text = trama;
                    trama = "\n";
                    if (data[data.IndexOf('B') + 2].Equals('0'))
                    {
                        textBox10.Text = "   LOW";
                    }
                    else
                    {
                        textBox10.Text = "   HIGH";
                    }
                }
                file.Close();
            }

            catch (IOException)
            {
                textBox9.Text = "File is in use";
                //the file is unavailable because it is:
                //still being written to
                //or being processed by another thread
                //or does not exist (has already been processed)
                return false;
            }

            //file is not locked
            return true;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (String.IsNullOrEmpty(savedPath))
                MessageBox.Show("Choose the file to open");
            else
                timer1.Start();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void richTextBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged_1(object sender, EventArgs e)
        {

        }

        private void textBox8_TextChanged(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            foreach (string s in SerialPort.GetPortNames())
            {
                listBox1.Items.Add(s);
            }
        }

        private void Update_data()
        {

            FileInfo f = new FileInfo(savedPath);

            if (f.Exists)
            {
                if (Read_File(savedPath))
                {
                    textBox9.Text = ("New Update");
                }
            }
            else
            {
                textBox9.Text = ("File do not exist");
            }
        }

        public void textBox9_TextChanged(object sender, EventArgs e)
        {

        }


        private void timer1_Tick(object sender, EventArgs e)
        {
            Update_data();
        }




        private void label10_Click(object sender, EventArgs e)
        {

        }

        private void textBox10_TextChanged(object sender, EventArgs e)
        {

        }

        private void tableLayoutPanel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void fontDialog1_Apply(object sender, EventArgs e)
        {

        }

        private void button3_Click_1(object sender, EventArgs e)
        {

        }

        private void progressBar1_Click(object sender, EventArgs e)
        {

        }

        private void richTextBox1_TextChanged_1(object sender, EventArgs e)
        {

        }

        private void button4_Click(object sender, EventArgs e)
        {

        }

        private void button4_Click_1(object sender, EventArgs e)
        {

            if (String.IsNullOrEmpty(COM))
            {
                MessageBox.Show("Choose COM");
            }
            else
            {
                Metodos_Porta_Serie Porta_Serie = new Metodos_Porta_Serie();
                if (Porta_Serie.Inicializar_Porta(COM, 9600) == true)
                {
                    textBox8.Text = "       ON   ";
                }
                else
                {
                    Porta_Serie.Fechar_Porta();

                    textBox8.Text = "       OFF   ";
                }
            }
        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void textBox11_TextChanged(object sender, EventArgs e)
        {

        }

        private void listBox1_SelectedIndexChanged_1(object sender, EventArgs e)
        {
            COM = listBox1.SelectedItem.ToString();
            textBox11.Text = "      " + COM;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            string dummyFileName = "WS_data.txt";

            OpenFileDialog sf = new OpenFileDialog();
            // Feed the dummy name to the save dialog
            sf.FileName = dummyFileName;

            if (sf.ShowDialog() == DialogResult.OK)
            {
                // Now here's our save folder
                savedPath = sf.FileName;
                textBox9.Text = savedPath;
            }
        }

        private void textBox12_TextChanged(object sender, EventArgs e)
        {

        }

        private void timer2_Tick(object sender, EventArgs e)
        {

        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

    }
}


