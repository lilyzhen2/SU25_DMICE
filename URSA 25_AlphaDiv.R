# Author: Lily Zhen
# Description: Alpha diversity analyses 

library(phyloseq)
library(microbiome)
library(tidyverse)

### Set up data
# Load phyloseq object
ps <- readRDS("~/mouse proj/DATA/chronic_pain_2025-01-22_output_phyloseq.rds")

# rarefy phyloseq object
# This ensures the samples have consistent read lengths
ps_rare <- rarefy_even_depth(ps, rngseed = 2)

### Comparing Variables

# Create a data.frame with:
# Alpha diversity measures (Observed, Shannon, Simpson, Fisher)
# Variables of interest (status, sex, cohort)
adiv <- data.frame(
  "Observed" = phyloseq::estimate_richness(ps_rare, measures = "Observed"),
  "Shannon" = phyloseq::estimate_richness(ps_rare, measures = "Shannon"),
  "Simpson" = phyloseq::estimate_richness(ps_rare, measures = "Simpson"),
  "Fisher" = phyloseq::estimate_richness(ps_rare, measures = "Fisher"),
  "Sex" = phyloseq::sample_data(ps_rare)$sex,
  "Status" = phyloseq::sample_data(ps_rare)$status,
  "Cohort" = phyloseq::sample_data(ps_rare)$cohort)

## Visualizing Alpha Diversity with Boxplots
# Plot code from:
# https://www.nicholas-ollberding.com/post/introduction-to-the-statistical-analysis-of-microbiome-data-in-r/

# Status Comparison 
adiv %>%
  gather(key = metric, value = value, c("Observed", "Shannon", 
                                        "Simpson", "Fisher")) %>%
  mutate(metric = factor(metric, levels = c("Observed", "Shannon", 
                                            "Simpson", "Fisher"))) %>%
  ggplot(aes(x = Status, y = value)) +
  geom_boxplot(outlier.color = NA) +
  geom_jitter(aes(color = Status), height = 0, width = .2) +
  labs(title = "Alpha Diversity Measures Between Cases & Controls",
       x = "", y = "Diversity Value") +
  facet_wrap(~ metric, scales = "free") +
  theme(legend.position = "none")

# Sex Comparison
adiv %>%
  gather(key = metric, value = value, c("Observed", "Shannon", 
                                        "Simpson", "Fisher")) %>%
  mutate(metric = factor(metric, levels = c("Observed", "Shannon", 
                                            "Simpson", "Fisher"))) %>%
  ggplot(aes(x = Sex, y = value)) +
  geom_boxplot(outlier.color = NA) +
  geom_jitter(aes(color = Sex), height = 0, width = .2) +
  labs(title = "Alpha Diversity Measures Between Sexes",
       x = "", y = "Diversity Value") +
  facet_wrap(~ metric, scales = "free") +
  theme(legend.position = "none")

# Cohort Comparison
adiv %>%
  gather(key = metric, value = value, c("Observed", "Shannon", 
                                        "Simpson", "Fisher")) %>%
  mutate(metric = factor(metric, levels = c("Observed", "Shannon", 
                                            "Simpson", "Fisher"))) %>%
  ggplot(aes(x = Cohort, y = value)) +
  geom_boxplot(outlier.color = NA) +
  geom_jitter(aes(color = Cohort), height = 0, width = .2) +
  labs(title = "Alpha Diversity Measures Between Cohorts",
       x = "", y = "Diversity Value") +
  facet_wrap(~ metric, scales = "free") +
  theme(legend.position = "none")

## 2-Variable Significance Test (Wilcoxon Rank-Sum Test)

# All p-values returned insignificant for status comparison
wilcox.test(Observed ~ Status, data = adiv)
wilcox.test(Shannon ~ Status, data = adiv)
wilcox.test(Simpson ~ Status, data = adiv)
wilcox.test(Fisher ~ Status, data = adiv)

# All p-values returned insignificant for sex comparison
wilcox.test(Observed ~ Sex, data = adiv)
wilcox.test(Shannon ~ Sex, data = adiv)
wilcox.test(Simpson ~ Sex, data = adiv)
wilcox.test(Fisher ~ Sex, data = adiv)

## 2+ Variable Significance Test (Kruskal-Wallis Test)

# All p-values returned insignificant for cohort comparison
kruskal.test(Shannon ~ Cohort, data = adiv)
kruskal.test(Observed ~ Cohort, data = adiv)
kruskal.test(Simpson ~ Cohort, data = adiv)
kruskal.test(Fisher ~ Cohort, data = adiv)

