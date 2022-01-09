# !/bin/bash
# cite code from Eugene Chou Lab section on Friday.
rm -f /tmp/length.dat
rm -f /tmp/maxvalue.dat
rm -f /tmp/lengthdots.dat
rm -f /tmp/frequency.dat
# remove all the file I will meke incase I creat them eariler.

for n in {2..10000}; do # According to asgn1.pdf, the n should from 2 to 10000
	echo -n $n\  >> /tmp/length.dat # length.dat will contain all the dots for figure2. 
	                                # the x-coordinate should be the value of n
	echo -n $n\  >> /tmp/maxvalue.dat # maxvalue.dat will contain all the dots for figure3
	                                  # the x-coordinate should be the value of n
	./collatz -n $n | wc -l >> /tmp/length.dat     # Place the data points(the lenth of each sequence) 
	                                               # into a length.dat file as y-coordinate.
	./collatz -n $n | sort -n |tail -n 1 >> /tmp/maxvalue.dat # Place the data points(the max value of each sequence) 
	                                                          # into a maxvalue.dat file as y-coordinate.
	./collatz -n $n | wc -l >> /tmp/lengthdots.dat # lengthdots.dat will contine the length of each sequence from 2 to 10000.
done

cat /tmp/lengthdots.dat | sort -n | uniq -c >> /tmp/frequency.dat # /tmp/lengthdots.dat will contain all the dots for figure4. 
                                                                  # uniq -c will count the frequency of each length in the lengthdots.dat.


# This is the heredoc that is sent to gnuplot.
# The idea is from the plot.sh in the given resources folder.
gnuplot <<END
    set terminal pdf
    set output "figure2.pdf"
    set title "Collatz Sequence Lengths"
    set xlabel "n"
    set ylabel "length"
    set zeroaxis
    plot "/tmp/length.dat" with dots title ""
END


gnuplot <<END
    set terminal pdf
    set output "figure3.pdf"
    set title "Maximum Collatz Sequence Value"
    set xlabel "n"
    set ylabel "value"
    set yrange [0:100000]
    set zeroaxis
    plot "/tmp/maxvalue.dat" with dots title ""
END

gnuplot <<END
    set terminal pdf
    set output "figure4.pdf"
    set title "Collatz Sequence Length Histogram"
    set xlabel "frequency"
    set ylabel "length"
    set xrange [0:225]
    set boxwidth 0.01 relative
    set style fill solid 1.0
    plot "/tmp/frequency.dat" using 2:1 with boxes title ""
END
