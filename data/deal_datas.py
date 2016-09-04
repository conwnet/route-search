# --- File ---
# stops.txt
# stop_times.txt
# callendar.txt
# trips.txt
# transfers.txt

file_stops = open('stops.txt')
file_stop_times = open('stop_times.txt')
file_calendar = open('calendar.txt')
file_trips = open('trips.txt')
file_transfers = open('transfers.txt')
file_calendar_out = open('calendar.in', 'w')
file_stop_out = open('stops.in', 'w')
file_stop_times_out = open('stop_times.in', 'w')
file_transfers_out = open('transfers.in', 'w')


#read from stops.txt to get the id  (stop_id => id)
file_stops.readline()
lines = file_stops.readlines()
dic_stop_id = {}
stop_count = 1
for line in lines :
    line = line.split(',')
    dic_stop_id[line[0]] = str(stop_count)
    file_stop_out.write(str(stop_count) + ' ' + line[2] + ' ' + line[4] + ' ' + line[5] + '\n')
    stop_count += 1

#read from trips.txt to get the service_id  (trip_id => service_id)
file_trips.readline()
lines = file_trips.readlines()
dic_trip_id = {} # service id
hash_trip_id = {} # integer trip id
for line in lines :
    line = line.split(',')
    dic_trip_id[line[2]] = line[1]
    if line[2] not in hash_trip_id.keys():
        hash_trip_id[line[2]] = str(len(hash_trip_id) + 1)

#read from stop_times.txt and output
file_stop_times.readline()
lines = file_stop_times.readlines()
#keep unique
#lines = list(set(lines))
for i in range(len(lines)) :
    lines[i] = lines[i].split(',')
lines.sort(key=lambda x: [x[0], int(x[4])])

def format_time(tms) :
    time = tms.split(':')
    return (int(time[0]) % 24) * 3600 + int(time[1]) * 60 + int(time[2])

def time_interval(t1, t2):
    t1 = t1.split(':')
    t2 = t2.split(':')
    return (int(t2[0]) - int(t1[0])) * 3600 + (int(t2[1]) - int(t1[1])) * 60 + (int(t2[2]) - int(t1[2]))

for i in range(len(lines)) :
    if lines[i][0] not in hash_trip_id.keys():
        hash_trip_id[lines[i][0]] = str(len(hash_trip_id) + 1)
    if i == 0 or lines[i-1][0] != lines[i][0] :
    	continue
    file_stop_times_out.write(dic_stop_id[lines[i-1][3]] + ' ' + dic_stop_id[lines[i][3]] + ' ' + str(format_time(lines[i-1][2])) + ' ' + str(time_interval(lines[i - 1][2], lines[i][1])) + ' ' + hash_trip_id[lines[i-1][0]] + ' ' + dic_trip_id[lines[i-1][0]]  + '\n')
#	file_stop_times_out.write(dic_trip_id[line[0]] + ' ' + line[1] + ' ' + line[2] + ' ' + dic_stop_id[line[3]] + ' ' + line[0] + ' ' + line[4] + '\n')


#read from calendar.txt and output
file_calendar.readline()
content = file_calendar.read()
file_calendar_out.write(content.replace(',', ' '))

#read from transfers.txt and output
file_transfers.readline()
lines = file_transfers.readlines()
for line in lines :
    line = line.split(',')
    file_transfers_out.write(dic_stop_id[line[0]] + ' ' + dic_stop_id[line[1]] + ' ' + line[3] + '\n')
