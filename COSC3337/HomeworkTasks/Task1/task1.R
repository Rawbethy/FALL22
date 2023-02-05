install.packages("tidyverse")
install.packages("multipanelfigure")
install.packages("rpart")
install.packages("rpart.plot")
install.packages("caTools")
library(ggplot2)
library(multipanelfigure)
library(rpart)
library(rpart.plot)
library(caTools)
maritalData <-  read.csv("C:\\Users\\rober\\OneDrive\\Desktop\\FALL22\\COSC3337\\HomeworkTasks\\Task1\\Marriage_Divorce_DB.csv", header=TRUE, stringsAsFactors=FALSE)

#Create new column "Recommendation" for Decision to Divorce or Marry
Recommendation <- rep(NA, nrow(maritalData))
for(x in 1:nrow(maritalData)) {
  if(maritalData$Divorce.Probability[x] >= 1 & maritalData$Divorce.Probability[x] < 2) {
    Recommendation[x] = "Marry"
  }
  else {
    Recommendation[x] = "Divorce"
  }
}
maritalData <- cbind(maritalData, Recommendation)
# Subtask 1: Find covariance of the given variables; Age gap, Economic Similarity, Common Interests and Divorce Probability

covData <-  subset(maritalData, select=c("Age.Gap", "Economic.Similarity", "Common.Interests", "Divorce.Probability"))
covDataNorm <- log(as.data.frame(covData))
show(cov(covDataNorm))
show(cor(covDataNorm))
# Here we are given the covariance matrix of all 4 attributes of the dataset. When the covariance is positive
# that means that the two attributes are directly related to each other meaning when one value goes up, the other value
# will do the same. The opposite is assumed for a negative covariance. Looking at this matrix, we can infer that
# the only variable that are directly related will be (Divorce Probability - Age Gap) and (Common Interests - Economic Stability).
# All other compared variables will not be directly related. 

# Subtask 2: Create a scatter plot for the attributes Common Interests and Love. Interpret the scatter plot

scatterData <- subset(maritalData, select=c("Common.Interests", "Love"))
X11()
ggplot(scatterData, aes(x = Common.Interests, y = Love)) +
  geom_point()
show(cov(log(as.data.frame(scatterData))))
# This plot Common Interests vs. Love is shown to be very indirectly related. There is no structure to the points being plotted therefore there is no
# relationship between common interest and love between two people

# Subtask 3: Create histograms for Divorce, Desire to Marry, and Common Interests attributes for both the Marry and the Divorce recommendations
subMarry <- which(maritalData$Recommendation == "Marry")
subDivorce <- which(maritalData$Recommendation == "Divorce")
p1 <- ggplot(maritalData[subMarry,], aes(x=Divorce.Probability)) + geom_histogram(bins=15, fill="red", col=I("yellow")) + xlab("Divorce Probability") + ylab("Frequency")
p2 <- ggplot(maritalData[subMarry,], aes(x=Desire.to.Marry)) + geom_histogram(bins=15, fill="blue", col=I("red")) + xlab("Desire To Marry") + ylab("Frequency")
p3 <- ggplot(maritalData[subMarry,], aes(x=Common.Interests)) + geom_histogram(bins=15, fill="green", col=I("red")) + xlab("Common Interests") + ylab("Frequency")
p4 <- ggplot(maritalData[subDivorce,], aes(x=Divorce.Probability)) + geom_histogram(bins=15, fill="red", col=I("yellow")) + xlab("Divorce Probability") + ylab("Frequency")
p5 <- ggplot(maritalData[subDivorce,], aes(x=Desire.to.Marry)) + geom_histogram(bins=15, fill="blue", col=I("red")) + xlab("Desire To Marry") + ylab("Frequency")
p6 <- ggplot(maritalData[subDivorce,], aes(x=Common.Interests)) + geom_histogram(bins=15, fill="green", col=I("red")) + xlab("Common Interests") + ylab("Frequency")
X11()
figure <- multi_panel_figure(columns = 3, rows = 2, panel_label_type = "none")
figure %<>%
  fill_panel(p1, column = 1, row = 1) %<>%
  fill_panel(p2, column = 2, row = 1) %<>%
  fill_panel(p3, column = 3, row = 1) %<>%
  fill_panel(p4, column = 1, row = 2) %<>%
  fill_panel(p5, column = 2, row = 2) %<>%
  fill_panel(p6, column = 3, row = 2) 
figure


# Subtask 4
X11()
p1 <- ggplot(maritalData, aes(x=Recommendation, y=Self.Confidence, fill=Recommendation)) + geom_boxplot() + xlab("Recommendation") + ylab("Self Confidence")
p2 <- ggplot(maritalData, aes(x=factor(0), y=Self.Confidence)) + geom_boxplot(fill="yellow") + theme(legend.position="none") + xlab("Marry & Divorce") + ylab("Self Confidence")
figure <- multi_panel_figure(columns=5, rows=1, panel_label_type = "none")
figure %<>%
  fill_panel(p1, column = 1:3, row = 1) %<>%
  fill_panel(p2, column = 4:5, row = 1)
figure

# subtask 5
X11()
p1 <- ggplot(maritalData, aes(Economic.Similarity, Common.Interests, color=Recommendation)) + geom_point() + geom_smooth(method = "lm", formula = y ~ x) + theme(legend.title = element_text(size = 7.5)) + labs(x="Economic Similarity", y="Common Interests")
p2 <- ggplot(maritalData, aes(Common.Interests, Loyalty, color=Recommendation)) + geom_point() + geom_smooth(method = "lm", formula = y ~ x) + theme(legend.title = element_text(size = 7.5)) + labs(x="Common Interests", y="Loyalty")
p3 <- ggplot(maritalData, aes(Loyalty, Economic.Similarity, color=Recommendation)) + geom_point() + geom_smooth(method = "lm", formula = y ~ x) + theme(legend.title = element_text(size = 7.5)) + labs(x="Loyalty", y="Economic Similarity")
figure <- multi_panel_figure(columns = 6, rows = 2, panel_label_type = "none")
figure %<>%
  fill_panel(p1, column = 1:3, row = 1) %<>%
  fill_panel(p2, column = 4:6, row = 1) %<>%
  fill_panel(p3, column = 2:5, row = 2)
figure

# subtask 6
X11()
ggplot(maritalData, aes(x=Age.Gap, color=Recommendation, fill=Recommendation, alpha=.4)) + geom_density(size=.7)  + labs(x = "Age Gap", title = "Age Gap Density Plot") + guides(alpha="none")
X11()
ggplot(maritalData, aes(x=Social.Gap, color=Recommendation, fill=Recommendation, alpha=.4)) + geom_density(size=.7)  + labs(x = "Social Gap", title = "Social Gap Density Plot") + guides(alpha="none")


# subtask 7
zscores = data.frame(matrix(nrow = 100, ncol = 0))
for(x in 1:(ncol(maritalData)-2)) {
  c <- (maritalData[,x] - mean(maritalData[,x]))/sd(maritalData[,x])
  zscores <- cbind(zscores, c)
}
colnames(zscores) = names(maritalData[1:30])

model <- lm(maritalData$Divorce.Probability ~ ., data = zscores)
summary(model)


# subtask 8
newData1 <- data.frame(maritalData[c(1, 3:10, 12:30, 32)])
newData2 <- data.frame(maritalData[c(13:21, 32)])
newData3 <- data.frame(maritalData[c(22:30, 32)])

sample_data1 = sample.split(newData1, SplitRatio = 0.8)
train_data1 <- subset(newData1, sample_data1 == TRUE)
test_data1 <- subset(newData1, sample_data1 == FALSE)
model1 <- rpart(Recommendation ~., data = train_data1, control = list(maxdepth = 10), method = 'class')

sample_data2 = sample.split(newData2, SplitRatio = 0.8)
train_data2 <- subset(newData2, sample_data2 == TRUE)
test_data2 <- subset(newData2, sample_data2 == FALSE)
model2 <- rpart(Recommendation ~., data = train_data2)

sample_data3 = sample.split(newData3, SplitRatio = 0.8)
train_data3 <- subset(newData3, sample_data3 == TRUE)
test_data3 <- subset(newData3, sample_data3 == FALSE)
model3 <- rpart(Recommendation ~., data = train_data3)

X11()
rpart.plot(model1)
X11()
rpart.plot(model2)
X11()
rpart.plot(model3)

predict1 <- predict(model1, test_data1, type = 'class')
table1 = table(test_data1$Recommendation, predict1)
test1_accuracy <- sum(diag(table1)) / sum(table1)
print(paste("Accuracy for first test", test1_accuracy))

predict2 <- predict(model2, test_data2, type = 'class')
table2 = table(test_data2$Recommendation, predict2)
test2_accuracy <- sum(diag(table2)) / sum(table2)
print(paste("Accuracy for second test", test2_accuracy))

predict3 <- predict(model3, test_data3, type = 'class')
table3 = table(test_data3$Recommendation, predict3)
test3_accuracy <-  sum(diag(table3)) / sum(table3)
print(paste("Accuracy for third test", test3_accuracy))