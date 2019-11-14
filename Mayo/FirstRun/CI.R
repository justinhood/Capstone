setwd("~/Desktop/PSM/Fall 2019/Capstone/Mayo/FirstRun")
rm(list = ls())
zstar <- qnorm(.975)
duration <- 12*60

##### Oral Incoming Stats
X <- read.csv("OralIncomingCounts.txt", header = FALSE)
oralIn <- X[,1]
mu=mean(oralIn)
s=sd(oralIn)
delta <- zstar*s/sqrt(length(oralIn))
(lowerOralIn<- mu-delta)
(upperOralIn<- mu+delta)

##### IV Incoming Stats
X <- read.csv("IVIncomingCounts.txt", header = FALSE)
ivIn <- X[,1]
mu=mean(ivIn)
s=sd(ivIn)
delta <- zstar*s/sqrt(length(ivIn))
(lowerIVIn<- mu-delta)
(upperIVIn<- mu+delta)

##### Entry Queue Lengths
X <- read.csv("entryQueueCounts.txt", header = FALSE)
X <- t(X)
X<-X[-dim(X)[1],]
entryQ <- colMeans(X)
mu=mean(entryQ)
s=sd(entryQ)
delta <- zstar*s/sqrt(length(entryQ))
(lowerEntryQ<- mu-delta)
(upperEntryQ<- mu+delta)

##### Entry Verification Queue Lengths
X <- read.csv("entryVerQueueCounts.txt", header = FALSE)
X <- t(X)
X<-X[-dim(X)[1],]
entryVerQ <- colMeans(X)
mu=mean(entryVerQ)
s=sd(entryVerQ)
delta <- zstar*s/sqrt(length(entryVerQ))
(lowerEntryVerQ<- mu-delta)
(upperEntryVerQ<- mu+delta)

##### Oral Fill Queue Lengths
X <- read.csv("oralFillQueueCounts.txt", header = FALSE)
X <- t(X)
X<-X[-dim(X)[1],]
oralFillQ <- colMeans(X)
mu=mean(oralFillQ)
s=sd(oralFillQ)
delta <- zstar*s/sqrt(length(oralFillQ))
(lowerOralFillQ<- mu-delta)
(upperOralFillQ<- mu+delta)

##### IV Fill Queue Lengths
X <- read.csv("ivFillQueueCounts.txt", header = FALSE)
X <- t(X)
X<-X[-dim(X)[1],]
ivFillQ <- colMeans(X)
mu=mean(ivFillQ)
s=sd(ivFillQ)
delta <- zstar*s/sqrt(length(ivFillQ))
(lowerIVFillQ<- mu-delta)
(upperIVFillQ<- mu+delta)

##### Fill Verfification Queue Lengths
X <- read.csv("fillVerQueueCounts.txt", header = FALSE)
X <- t(X)
X<-X[-dim(X)[1],]
fillVerQ <- colMeans(X)
mu=mean(fillVerQ)
s=sd(fillVerQ)
delta <- zstar*s/sqrt(length(fillVerQ))
(lowerFillVerQ<- mu-delta)
(upperFillVerQ<- mu+delta)

##### Dispense Queue Lengths
X <- read.csv("dispQueueCounts.txt", header = FALSE)
X <- t(X)
X<-X[-dim(X)[1],]
dispQ <- colMeans(X)
mu=mean(dispQ)
s=sd(dispQ)
delta <- zstar*s/sqrt(length(dispQ))
(lowerDispQ<- mu-delta)
(upperDispQ<- mu+delta)

#### Oral Filled Stats
X <- read.csv("oralFilled.txt", header = FALSE)
oralOut <- X[,1]
mu=mean(oralOut)
s=sd(oralOut)
delta <- zstar*s/sqrt(length(oralOut))
(lowerOralOut<- mu-delta)
(upperOralOut<- mu+delta)

#### IV Filled Stats
X <- read.csv("ivFilled.txt", header = FALSE)
ivOut <- X[,1]
mu=mean(ivOut)
s=sd(ivOut)
delta <- zstar*s/sqrt(length(ivOut))
(lowerIVOut<- mu-delta)
(upperIVOut<- mu+delta)

#### Pharmacist Idle Times
X <- read.csv("pharmIdle.txt", header = FALSE)
X <- t(X)
X<-X[-dim(X)[1],]
pharmIdle <- colMeans(X)
# These will be percentages right now, can remove if desired
mu=mean(pharmIdle)/duration*100
s=sd(pharmIdle)/duration*100
delta <- zstar*s/sqrt(length(pharmIdle))
(lowerPharmIdle<- mu-delta)
(upperPharmIdle<- mu+delta)

## Normal Technician Idle Times
X <- read.csv("techIdle.txt", header = FALSE)
X <- t(X)
X<-X[-dim(X)[1],]
techIdle <- colMeans(X)
# These will be percentages right now, can remove if desired
mu=mean(techIdle)/duration*100
s=sd(techIdle)/duration*100
delta <- zstar*s/sqrt(length(techIdle))
(lowerTechIdle<- mu-delta)
(upperTechIdle<- mu+delta)

## Normal Technician Idle Times
X <- read.csv("ivTechIdle.txt", header = FALSE)
X <- t(X)
X<-X[-dim(X)[1],]
ivTechIdle <- X
# These will be percentages right now, can remove if desired
mu=mean(ivTechIdle)/duration*100
s=sd(ivTechIdle)/duration*100
delta <- zstar*s/sqrt(length(ivTechIdle))
(lowerIVTechIdle<- mu-delta)
(upperIVTechIdle<- mu+delta)

### Oral Throughput Times
no_col <- max(count.fields("oralTotals.txt", sep = ","))
X <- read.table("oralTotals.txt" ,sep=",",fill=TRUE,header = F,col.names=c("chr", "start", "end", "length",1:no_col))
X <- t(X)
oralThrough <- colMeans(X, na.rm=TRUE)
#Convert from steps to minutes
oralThrough <- oralThrough*toc
mu=mean(oralThrough)
s=sd(oralThrough)
delta <- zstar*s/sqrt(length(oralThrough))
(lowerOralThrough<- mu-delta)
(upperOralThrough<- mu+delta)

### IV Throughput Times
no_col <- max(count.fields("ivTotals.txt", sep = ","))
X <- read.table("ivTotals.txt" ,sep=",",fill=TRUE,header = F,col.names=c("chr", "start", "end", "length",1:no_col))
X <- t(X)
ivThrough <- colMeans(X, na.rm=TRUE)
#Convert from steps to minutes
ivThrough <- ivThrough*toc
mu=mean(ivThrough)
s=sd(ivThrough)
delta <- zstar*s/sqrt(length(ivThrough))
(lowerIVThrough<- mu-delta)
(upperIVThrough<- mu+delta)
