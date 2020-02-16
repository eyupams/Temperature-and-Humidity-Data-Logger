import serial
import psycopg2
import time
    
def connect():
    conn = None
    try:
        print("Connecting to the PostgreSQL database...")
        
        #Insert database credentials
        conn = psycopg2.connect("")
        
        print("Accessing device")
        arduino = serial.Serial("COM3", 9600)
        while True:
            cur = conn.cursor()
            data = arduino.readline()
            data = data.decode("utf-8")
            pieces = data.split("\t")
            print(data)
            try:
                cur.execute("INSERT INTO weather (date, temp, humid) VALUES (%s, %s, %s)", (pieces[0],pieces[1], pieces[2]))
                conn.commit()
                cur.close()
            except (Exception, psycopg2.DatabaseError) as error:
                print(error)
            finally:
                cur.close()

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
    finally:
        if conn is not None:
            conn.close()
            print('Database connection closed.')

if __name__ == '__main__':
    connect()